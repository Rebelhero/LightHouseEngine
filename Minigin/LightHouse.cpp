#include "LightHousePCH.h"
#include "LightHouse.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"

using namespace std;
using namespace std::chrono;

dae::LightHouse::LightHouse(float tickRate)
{
	m_FixedTimeStep = tickRate;
}

void dae::LightHouse::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::LightHouse::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto background = std::make_shared<RenderComponent>(go, "background.jpg");
	go->AddComponent(std::move(background));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto logo = std::make_shared<RenderComponent>(go, "logo.png");
	go->AddComponent(logo);
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<TextComponent>(go, "Programming 4 Assignment", font);
	go->AddComponent(std::move(textComponent));
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto newFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(std::make_shared<FPSCounterComponent>(go, newFont));
	go->SetPosition(20, 30);
	scene.Add(go);
}

void dae::LightHouse::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::LightHouse::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float tickDelta = 0.f;	//the value that gets reduced by msPerUpdate

		sceneManager.Start();

		//while (doContinue)
		//{
		//	auto currentTime = high_resolution_clock::now();
		//	float deltaTime = duration<float>(currentTime - lastTime).count();

		//	doContinue = input.ProcessInput();
		//	sceneManager.Update(deltaTime);
		//	renderer.Render();

		//	lastTime = currentTime;
		//}

		while (doContinue)
		{
			auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			tickDelta += deltaTime;
			doContinue = input.ProcessInput();

			while (tickDelta >= m_FixedTimeStep)
			{
				sceneManager.Update(m_FixedTimeStep);
				tickDelta -= m_FixedTimeStep;
			}

			renderer.Render();
		}
	}

	Cleanup();
}

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

Engine::LightHouse::LightHouse(float tickRate)
{
	m_FixedTimeStep = tickRate;
	Initialize();
}

void Engine::LightHouse::Initialize()
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

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}

/**
 * Code constructing the scene world starts here
 */
void Engine::LightHouse::LoadGame() const
{

}

void Engine::LightHouse::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Engine::LightHouse::Run()
{
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float tickDelta = 0.f;	//the value that gets reduced by msPerUpdate

		sceneManager.Start();

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

#include "LightHousePCH.h"
#include "MainScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"

MainScene::MainScene(const std::string& name)
	: Scene(name)
{
}

void MainScene::Start()
{
	auto go = std::make_shared<Engine::GameObject>();
	auto background = std::make_shared<Engine::RenderComponent>(go, "background.jpg");
	go->AddComponent(std::move(background));
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto logo = std::make_shared<Engine::RenderComponent>(go, "logo.png");
	go->AddComponent(logo);
	go->SetPosition(216, 180);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<Engine::TextComponent>(go, "Programming 4 Assignment", font);
	go->AddComponent(std::move(textComponent));
	go->SetPosition(80, 20);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto newFont = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(std::make_shared<Engine::FPSCounterComponent>(go, newFont));
	go->SetPosition(20, 30);
	Add(go);

	//Base Start for every added component
	Scene::Start();
}
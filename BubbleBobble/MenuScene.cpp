#include "LightHousePCH.h"
#include "MenuScene.h"
#include <memory>
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "MenuSelectComponent.h"

MenuScene::MenuScene(const std::string& name, int windowScale)
	: Scene(name)
	, m_WindowScale{ windowScale }
{
	auto go = std::make_shared<Engine::GameObject>();
	auto texture = Engine::ResourceManager::GetInstance().LoadTexture("title.png");
	auto background = std::make_shared<Engine::RenderComponent>(go, texture);
	go->AddComponent(std::move(background));
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<Engine::TextComponent>(go, "Programming 4 Assignment", font);
	go->AddComponent(std::move(textComponent));
	go->SetPosition(80, 20);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	textComponent = std::make_shared<Engine::TextComponent>(go, "Press A for Singleplayer, B for Coop", font);
	go->AddComponent(std::move(textComponent));
	go->SetPosition(80, 450);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto menuSelect = std::make_shared<Engine::MenuSelectComponent>(go);
	go->AddComponent(std::move(menuSelect));
	Add(go);

	//Base Start for every added component
	Scene::Start();
}

void MenuScene::Start()
{
}

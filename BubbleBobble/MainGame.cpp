#include "LightHousePCH.h"
#include "LightHouse.h"
#include "MainGame.h"

//added scenes
#include "SceneManager.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "Level02Single.h"
#include "Level03Single.h"
#include "MainSceneCoop.h"
#include "Level02Coop.h"
#include "Level03Coop.h"

void MainGame::Run()
{
	Engine::LightHouse engine{ 0.0167f, 2 };

	//add scenes here:
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<MainScene>("MainScene", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<MenuScene>("MenuScene", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<Level02Single>("Level02Single", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<Level03Single>("Level03Single", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<MainSceneCoop>("MainSceneCoop", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<Level02Coop>("Level02Coop", engine.GetWindowScale()));
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<Level03Coop>("Level03Coop", engine.GetWindowScale()));

	Engine::SceneManager::GetInstance().ChangeCurrentScene("MenuScene");

	engine.Run();
}
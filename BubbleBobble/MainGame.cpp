#include "LightHousePCH.h"
#include "LightHouse.h"
#include "MainGame.h"

//added scenes
#include "SceneManager.h"
#include "MainScene.h"

void MainGame::Run()
{
	Engine::LightHouse engine{ 0.0167f };

	//add scenes here:
	Engine::SceneManager::GetInstance().AddScene(std::make_shared<MainScene>("MainScene"));

	engine.Run();
}
#include "LightHousePCH.h"
#include "MenuSelectComponent.h"
#include "SceneManager.h"
#include "InputManager.h"

Engine::MenuSelectComponent::MenuSelectComponent(const std::shared_ptr<GameObject>& owner)
	: BaseComponent(owner)
{
}

void Engine::MenuSelectComponent::Start()
{
}

void Engine::MenuSelectComponent::Update(float deltaTime)
{
	if (InputManager::GetInstance().IsPressed(0, Engine::ControllerButton::ButtonA) ||
		InputManager::GetInstance().IsPressed(0, (DWORD)0x41))	//0x41 == "A"-Key
		Engine::SceneManager::GetInstance().ChangeCurrentScene("MainScene");

	if (InputManager::GetInstance().IsPressed(0, Engine::ControllerButton::ButtonB) ||
		InputManager::GetInstance().IsPressed(0, 0x42))	//0x42 == "B"-Key
		Engine::SceneManager::GetInstance().ChangeCurrentScene("MainSceneCoop");
}

void Engine::MenuSelectComponent::Render()
{
}

#include "LightHousePCH.h"
#include "CharacterControllerComponent.h"
#include "InputManager.h"

Engine::CharacterControllerComponent::CharacterControllerComponent(const std::shared_ptr<GameObject>& owner, short playerID)
	: BaseComponent(owner)
	, m_PlayerID{ playerID }
{
	m_Commands.push_back(std::make_unique<MoveRightCommand>(Engine::ControllerButton::DPadRight, NULL));
	m_Commands.push_back(std::make_unique<MoveLeftCommand>(Engine::ControllerButton::DPadLeft, NULL));
	m_Commands.push_back(std::make_unique<JumpCommand>(Engine::ControllerButton::ButtonA, NULL));
}

void Engine::CharacterControllerComponent::Start()
{
}

void Engine::CharacterControllerComponent::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Commands.size(); i++)
	{
		if (InputManager::GetInstance().IsPressed(m_PlayerID, m_Commands[i]->GetButton()))
			m_Commands[i]->execute(deltaTime);

		if (InputManager::GetInstance().IsPressed(m_PlayerID, m_Commands[i]->GetKey()))
			m_Commands[i]->execute(deltaTime);
	}
}

void Engine::CharacterControllerComponent::Render()
{
}

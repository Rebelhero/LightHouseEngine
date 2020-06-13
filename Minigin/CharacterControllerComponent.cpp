#include "LightHousePCH.h"
#include "CharacterControllerComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "GameObject.h"
#include <memory>
#include <algorithm>
#include "ColliderComponent.h"
#include "EnemyControllerComponent.h"

using namespace Engine;

Engine::CharacterControllerComponent::CharacterControllerComponent(const std::shared_ptr<GameObject>& owner, int playerID,
	std::vector<std::shared_ptr<ColliderComponent>> levelCollision, std::vector<std::shared_ptr<EnemyControllerComponent>> enemies,
	int width, int height)
	: BaseComponent(owner)
	, m_PlayerID{ playerID }
	, m_LevelCollision{ levelCollision }
	, m_Enemies{ enemies }
	, m_Width{ width }
	, m_Height{ height }
{
	//Set up buttons for the different commands
	m_Commands.push_back(std::make_unique<MoveRightCommand>(Engine::ControllerButton::DPadRight, NULL));
	m_Commands.push_back(std::make_unique<MoveLeftCommand>(Engine::ControllerButton::DPadLeft, NULL));
	m_Commands.push_back(std::make_unique<JumpCommand>(Engine::ControllerButton::ButtonA, NULL));
	m_Commands.push_back(std::make_unique<ShootCommand>(Engine::ControllerButton::ButtonB, NULL));

	m_CurrentState = CharacterState::Idle;
	m_OldState = m_CurrentState;
}

void Engine::CharacterControllerComponent::Start()
{
	//TODO: Add Sprite Animation Component here
}

void Engine::CharacterControllerComponent::Update(float deltaTime)
{
	HandleInput();
	if (m_JumpCooldown >= 0.f)
		m_JumpCooldown -= deltaTime;
	if (m_InvincibilityTime >= 0.f)
		m_InvincibilityTime -= deltaTime;

	switch (m_CurrentState)
	{
	case CharacterState::MoveRight:
	{
		HandleMovement(false, deltaTime);
		break;
	}
	case CharacterState::MoveLeft:
	{
		HandleMovement(true, deltaTime);
		break;
	}
	case CharacterState::Idle:
	{
		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
		ApplyGravity(pTransform, deltaTime);
		break;
	}
	case CharacterState::Jump:
	{
		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();

		if (m_JumpCooldown > 0.f || !IsTouchingGround())
		{
			m_CurrentState = CharacterState::Idle;
			ApplyGravity(pTransform, deltaTime);
			break;
		}

		m_JumpCooldown = 0.5f;
		m_Velocity.y = -500.f;
		ApplyGravity(pTransform, deltaTime);
	}
	default:
		break;
	}

	//
	if (IsIntersectingWithEnemies() && m_InvincibilityTime <= 0.f)
	{
		m_Lives -= 1;
		m_InvincibilityTime = 5.f;

		//if (m_Lives < 0)
			//Change Scene
	}

	m_OldState = m_CurrentState;
}

void Engine::CharacterControllerComponent::Render()
{
}

void Engine::CharacterControllerComponent::HandleInput()
{
	//Reset state
	m_CurrentState = CharacterState::Idle;

	//Get the state to which we should transition into from input
	for (size_t i = 0; i < m_Commands.size(); i++)
	{
		if (InputManager::GetInstance().IsPressed(m_PlayerID, m_Commands[i]->GetButton()))
			m_Commands[i]->execute(m_CurrentState);

		if (InputManager::GetInstance().IsPressed(m_PlayerID, m_Commands[i]->GetKey()))
			m_Commands[i]->execute(m_CurrentState);
	}
}

void Engine::CharacterControllerComponent::HandleMovement(bool isMovingLeft, float deltaTime)
{
	std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
	float x{};
	if (isMovingLeft)
		x = pTransform->GetPosition().x - m_Speed * deltaTime;
	else
		x = pTransform->GetPosition().x + m_Speed * deltaTime;

	ApplyGravity(pTransform, deltaTime);
	//Collision Check
	if (IsIntersecting((int)x, (int)pTransform->GetPosition().y))	//return if the next move would intersect with something
		return;

	pTransform->SetPosition(x, pTransform->GetPosition().y, pTransform->GetPosition().z);
}

void Engine::CharacterControllerComponent::ApplyGravity(std::shared_ptr<Transform> transform, float deltaTime)
{
	m_Velocity.y += m_Acceleration.y * deltaTime;

	m_Velocity.y = std::clamp(m_Velocity.y, -1000.f, 150.f);
	float y{ transform->GetPosition().y + m_Velocity.y * deltaTime };

	if (IsIntersecting((int)transform->GetPosition().x, (int)y))
		return;

	transform->SetPosition(transform->GetPosition().x, y, transform->GetPosition().z);
}

bool Engine::CharacterControllerComponent::IsIntersecting(int x, int y)
{
	Rect characterRect{ x, y, m_Width, m_Height };
	bool isIntersecting{ false };

	for (size_t i = 0; i < m_LevelCollision.size(); i++)
	{
		if (m_LevelCollision[i]->IsIntersecting(characterRect, m_Velocity.y))
			isIntersecting = true;
	}

	return isIntersecting;
}

bool Engine::CharacterControllerComponent::IsIntersectingWithEnemies()
{
	std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
	Rect characterRect{ (int)pTransform->GetPosition().x, (int)pTransform->GetPosition().y, m_Width, m_Height };

	for (size_t i = 0; i < m_Enemies.size(); i++)
	{
		if (m_Enemies[i]->IsIntersecting(characterRect))
			return true;
	}

	return false;
}

bool Engine::CharacterControllerComponent::IsTouchingGround()
{
	std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
	Rect characterRect{ (int)pTransform->GetPosition().x, (int)pTransform->GetPosition().y, m_Width, m_Height };
	bool isTouchingGround{ false };

	for (size_t i = 0; i < m_LevelCollision.size(); i++)
	{
		if (m_LevelCollision[i]->IsTouchingGround(characterRect))
			isTouchingGround = true;
	}

	return isTouchingGround;
}

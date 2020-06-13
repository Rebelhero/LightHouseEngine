#include "LightHousePCH.h"
#include "EnemyControllerComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "GameObject.h"
#include <memory>
#include <algorithm>
#include "ColliderComponent.h"

using namespace Engine;

Engine::EnemyControllerComponent::EnemyControllerComponent(const std::shared_ptr<GameObject>& owner,
	std::vector<std::shared_ptr<ColliderComponent>> levelCollision, int width, int height)
	: BaseComponent(owner)
	, m_LevelCollision{ levelCollision }
	, m_Width{ width }
	, m_Height{ height }
{
	m_CurrentState = EnemyState::MoveLeft;
}

void Engine::EnemyControllerComponent::Start()
{
	//TODO: Add Sprite Animation Component here
}

void Engine::EnemyControllerComponent::Update(float deltaTime)
{
	if (m_FreezeTime >= 0.f)
		m_FreezeTime -= deltaTime;

	switch (m_CurrentState)
	{
	case EnemyState::MoveRight:
	{
		HandleMovement(false, deltaTime);
		break;
	}
	case EnemyState::MoveLeft:
	{
		HandleMovement(true, deltaTime);
		break;
	}
	case EnemyState::Idle:
	{
		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
		ApplyGravity(pTransform, deltaTime);
		break;
	}
	default:
		break;
	}
}

void Engine::EnemyControllerComponent::Render()
{
}

std::weak_ptr<GameObject> Engine::EnemyControllerComponent::GetOwner()
{
	return m_pOwner;
}

bool Engine::EnemyControllerComponent::IsIntersecting(Rect& other)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };

	return collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x &&
		collider.y < (other.y + other.height) &&
		(collider.y + collider.height) > other.y;
}

bool Engine::EnemyControllerComponent::IsFrozen()
{
	if (m_CurrentState == EnemyState::Idle)
		return true;
	else
		return false;
}

void Engine::EnemyControllerComponent::Trap()
{
	if (m_CurrentState == EnemyState::Idle)
		return;

	m_CurrentState = EnemyState::Idle;
	m_FreezeTime = 5.f;
}

void Engine::EnemyControllerComponent::HandleMovement(bool isMovingLeft, float deltaTime)
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
	{
		if (isMovingLeft)
			m_CurrentState = EnemyState::MoveRight;
		else
			m_CurrentState = EnemyState::MoveLeft;

		return;
	}

	pTransform->SetPosition(x, pTransform->GetPosition().y, pTransform->GetPosition().z);
}

void Engine::EnemyControllerComponent::ApplyGravity(std::shared_ptr<Transform> transform, float deltaTime)
{
	m_Velocity.y += m_Acceleration.y * deltaTime;

	m_Velocity.y = std::clamp(m_Velocity.y, -1000.f, 150.f);
	float y{ transform->GetPosition().y + m_Velocity.y * deltaTime };

	if (IsIntersecting((int)transform->GetPosition().x, (int)y))
		return;

	transform->SetPosition(transform->GetPosition().x, y, transform->GetPosition().z);
}

bool Engine::EnemyControllerComponent::IsIntersecting(int x, int y)
{
	std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
	Rect characterRect{ x, y, m_Width, m_Height };
	bool isIntersecting{ false };

	for (size_t i = 0; i < m_LevelCollision.size(); i++)
	{
		if (m_LevelCollision[i]->IsIntersecting(characterRect, m_Velocity.y))
			isIntersecting = true;
	}

	return isIntersecting;
}

bool Engine::EnemyControllerComponent::IsTouchingGround()
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

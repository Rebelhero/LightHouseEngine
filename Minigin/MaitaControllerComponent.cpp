#include "LightHousePCH.h"
#include "MaitaControllerComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "GameObject.h"
#include <memory>
#include <algorithm>
#include "ColliderComponent.h"
#include "BoulderComponent.h"

using namespace Engine;

Engine::MaitaControllerComponent::MaitaControllerComponent(const std::shared_ptr<GameObject>& owner,
	std::vector<std::shared_ptr<ColliderComponent>> levelCollision,
	std::shared_ptr<std::vector<std::shared_ptr<Engine::GameObject>>> boulders,
	int width, int height)
	: EnemyControllerComponent(owner, levelCollision, width, height)
	, m_Boulders{ boulders }
{
	m_CurrentState = EnemyState::MoveLeft;
	m_OldState = EnemyState::MoveLeft;
}

void Engine::MaitaControllerComponent::Start()
{
}

void Engine::MaitaControllerComponent::Update(float deltaTime)
{
	EnemyControllerComponent::Update(deltaTime);
	CheckBoulders();

	if (m_BoulderCooldown > 0.f)
		m_BoulderCooldown -= deltaTime;

	if (m_BoulderCooldown <= 0.f)
	{
		m_BoulderCooldown = 5.f;

		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
		auto pBoulder{ std::make_shared<Engine::GameObject>() };
		bool isMovingLeft{};

		if (m_CurrentState == EnemyState::MoveLeft)
			isMovingLeft = true;
		else
			isMovingLeft = false;

		pBoulder->SetPosition(pTransform->GetPosition().x, pTransform->GetPosition().y);
		pBoulder->AddComponent(std::make_shared<Engine::BoulderComponent>(pBoulder, isMovingLeft, 32, 32));
		m_Boulders->push_back(pBoulder);
		m_pOwner.lock()->AddChild(pBoulder);
	}
}

void Engine::MaitaControllerComponent::Render()
{
}

std::weak_ptr<GameObject> Engine::MaitaControllerComponent::GetOwner()
{
	return EnemyControllerComponent::GetOwner();
}

bool Engine::MaitaControllerComponent::IsIntersecting(Rect& other)
{
	return EnemyControllerComponent::IsIntersecting(other);
}

bool Engine::MaitaControllerComponent::IsFrozen()
{
	return EnemyControllerComponent::IsFrozen();
}

void Engine::MaitaControllerComponent::Trap()
{
	EnemyControllerComponent::Trap();
}

void Engine::MaitaControllerComponent::CheckBoulders()
{
	auto iterator = m_Boulders->begin();

	while (iterator != m_Boulders->end())
	{
		if ((*iterator)->GetComponent<BoulderComponent>()->GetRemainingLifeTime() <= 0.f)
		{
			m_pOwner.lock()->RemoveChild((*iterator));
			(*iterator)->RemoveComponent((*iterator)->GetComponent<RenderComponent>());
			iterator = m_Boulders->erase(iterator);
		}
		else
			iterator++;
	}
}

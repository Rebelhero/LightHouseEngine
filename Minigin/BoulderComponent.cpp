#include "LightHousePCH.h"
#include "BoulderComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <memory>

Engine::BoulderComponent::BoulderComponent(const std::shared_ptr<GameObject>& owner, bool isHeadingLeft,
	int width, int height)
	: BaseComponent(owner)
	, m_Width{ width }
	, m_Height{ height }
	, m_IsHeadingLeft{ isHeadingLeft }
{

}

void Engine::BoulderComponent::Start()
{
}

void Engine::BoulderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (!m_IsExecutedOnce)
	{
		Rect rect{ 0, 96, 16, 16 };
		auto texture = ResourceManager::GetInstance().LoadTexture("sprites3.png");
		auto bubbleSprite = std::make_shared<Engine::RenderComponent>(m_pOwner.lock(), texture, rect, 0, 0, 32, 32);
		m_pOwner.lock()->AddComponent(bubbleSprite);

		m_IsExecutedOnce = true;
	}

	if (m_FloatTime > 0.f)
	{
		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
		float x{};

		if (m_IsHeadingLeft)
			x = pTransform->GetPosition().x - m_Speed * deltaTime;
		else
			x = pTransform->GetPosition().x + m_Speed * deltaTime;

		pTransform->SetPosition((int)x, pTransform->GetPosition().y, pTransform->GetPosition().z);
		m_FloatTime -= deltaTime;
	}
}

void Engine::BoulderComponent::Render()
{
}

const std::weak_ptr<Engine::GameObject>& Engine::BoulderComponent::GetOwner()
{
	return m_pOwner;
}

bool Engine::BoulderComponent::IsIntersecting(Rect& other, float velocityY)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };

	bool isIntersecting = collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x &&
		collider.y < (other.y + other.height) &&
		(collider.y + collider.height) > other.y;

	return isIntersecting;
}

bool Engine::BoulderComponent::IsTouchingGround(Rect& other)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };
	int airMargin{ 4 };	//pixel margin for ground recognition

	return (collider.y - airMargin) < (other.y + other.height) &&
		other.y < collider.y&&
		collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x;
}

Rect Engine::BoulderComponent::GetRect()
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	return Rect(transform.x, transform.y, m_Width, m_Height);
}

float Engine::BoulderComponent::GetRemainingLifeTime()
{
	return m_FloatTime;
}

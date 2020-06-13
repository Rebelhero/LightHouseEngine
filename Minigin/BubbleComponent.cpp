#include "LightHousePCH.h"
#include "BubbleComponent.h"
#include "GameObject.h"

Engine::BubbleComponent::BubbleComponent(const std::shared_ptr<GameObject>& owner, bool isHeadingLeft,
	int width, int height, bool deactivateBottom)
	: BaseComponent(owner)
	, m_Width{ width }
	, m_Height{ height }
	, m_DeactivateBottom{ deactivateBottom }
	, m_IsHeadingLeft{ isHeadingLeft }
{

}

void Engine::BubbleComponent::Start()
{
}

void Engine::BubbleComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (!m_IsExecutedOnce)
	{
		Rect rect{ 0, 96, 16, 16 };
		auto bubbleSprite = std::make_shared<Engine::RenderComponent>(m_pOwner.lock(), "../Data/sprites2.png", rect, 0, 0, 32, 32);
		m_pOwner.lock()->AddComponent(bubbleSprite);

		m_IsExecutedOnce = true;
	}

	if (m_FloatTime > 0.f)
	{
		std::shared_ptr<Transform> pTransform = m_pOwner.lock()->GetTransform();
		int x{};

		if (m_IsHeadingLeft)
			x = pTransform->GetPosition().x - m_Speed * deltaTime;
		else
			x = pTransform->GetPosition().x + m_Speed * deltaTime;

		pTransform->SetPosition(x, pTransform->GetPosition().y, pTransform->GetPosition().z);
		m_FloatTime -= deltaTime;
	}
	else
	{
		////remove component
		//m_pOwner.lock()->RemoveComponent(this);
		////delete this;
	}
}

void Engine::BubbleComponent::Render()
{
}

bool Engine::BubbleComponent::IsIntersecting(Rect& other, float velocityY)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };

	bool isIntersecting = collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x &&
		collider.y < (other.y + other.height) &&
		(collider.y + collider.height) > other.y;

	//Allow the player to jump through platforms
	if (m_DeactivateBottom)
	{
		if (velocityY < 0.f)
			isIntersecting = false;
	}

	return isIntersecting;
}

bool Engine::BubbleComponent::IsTouchingGround(Rect& other)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };
	int airMargin{ 4 };	//pixel margin for ground recognition

	return (collider.y - airMargin) < (other.y + other.height) &&
		other.y < collider.y&&
		collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x;
}

Rect Engine::BubbleComponent::GetRect()
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	return Rect(transform.x, transform.y, m_Width, m_Height);
}

float Engine::BubbleComponent::GetRemainingLifeTime()
{
	return m_FloatTime;
}

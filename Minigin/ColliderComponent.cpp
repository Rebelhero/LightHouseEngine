#include "LightHousePCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"

Engine::ColliderComponent::ColliderComponent(const std::shared_ptr<GameObject>& owner, int width, int height, bool deactivateBottom)
	: BaseComponent(owner)
	, m_Width{ width }
	, m_Height{ height }
	, m_DeactivateBottom{ deactivateBottom }
{

}

void Engine::ColliderComponent::Start()
{
}

void Engine::ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Engine::ColliderComponent::Render()
{
}

bool Engine::ColliderComponent::IsIntersecting(Rect& other, float velocityY)
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

bool Engine::ColliderComponent::IsTouchingGround(Rect& other)
{
	auto transform = m_pOwner.lock()->GetTransform()->GetPosition();
	Rect collider{ (int)transform.x, (int)transform.y, m_Width, m_Height };
	int airMargin{ 4 };	//pixel margin for ground recognition

	return (collider.y - airMargin) < (other.y + other.height) &&
		other.y < collider.y&&
		collider.x < (other.x + other.width) &&
		(collider.x + collider.width) > other.x;
}

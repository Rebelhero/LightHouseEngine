#pragma once
#include "BaseComponent.h"

struct Rect;

namespace Engine
{
	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent(const std::shared_ptr<GameObject>& owner, int width, int height, bool deactivateBottom = false);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		bool IsIntersecting(Rect& other, float velocityY);
		bool IsTouchingGround(Rect& other);

		ColliderComponent(const ColliderComponent&) = delete;
		ColliderComponent(ColliderComponent&&) = delete;
		ColliderComponent& operator= (const ColliderComponent&) = delete;
		ColliderComponent& operator= (const ColliderComponent&&) = delete;

	private:
		int m_Width{};
		int m_Height{};
		bool m_DeactivateBottom{};
	};
}
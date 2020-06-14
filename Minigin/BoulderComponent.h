#pragma once
#include "BaseComponent.h"

struct Rect;

namespace Engine
{
	class GameObject;

	class BoulderComponent : public BaseComponent
	{
	public:
		BoulderComponent(const std::shared_ptr<GameObject>& owner, bool isHeadingLeft, int width, int height);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		const std::weak_ptr<GameObject>& GetOwner();
		bool IsIntersecting(Rect& other, float velocityY);
		bool IsTouchingGround(Rect& other);
		Rect GetRect();
		float GetRemainingLifeTime();

		BoulderComponent(const BoulderComponent&) = delete;
		BoulderComponent(BoulderComponent&&) = delete;
		BoulderComponent& operator= (const BoulderComponent&) = delete;
		BoulderComponent& operator= (const BoulderComponent&&) = delete;

	private:
		int m_Width{};
		int m_Height{};
		bool m_IsExecutedOnce{ false };
		bool m_IsHeadingLeft{};
		float m_Speed{ 100.f };
		float m_FloatTime{ 2.f };
	};
}
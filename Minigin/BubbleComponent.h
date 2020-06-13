#pragma once
#include "BaseComponent.h"

struct Rect;

namespace Engine
{
	class BubbleComponent : public BaseComponent
	{
	public:
		BubbleComponent(const std::shared_ptr<GameObject>& owner, bool isHeadingLeft, int width, int height, bool deactivateBottom);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		bool IsIntersecting(Rect& other, float velocityY);
		bool IsTouchingGround(Rect& other);
		Rect GetRect();
		float GetRemainingLifeTime();

		BubbleComponent(const BubbleComponent&) = delete;
		BubbleComponent(BubbleComponent&&) = delete;
		BubbleComponent& operator= (const BubbleComponent&) = delete;
		BubbleComponent& operator= (const BubbleComponent&&) = delete;

	private:
		int m_Width{};
		int m_Height{};
		bool m_DeactivateBottom{};
		bool m_IsExecutedOnce{ false };
		bool m_IsHeadingLeft{};
		float m_Speed{ 100.f };
		float m_FloatTime{ 2.f };
	};
}
#pragma once
#include "BaseComponent.h"
#include "FVector2.h"
#include "Transform.h"
#include "Rect.h"

class Command;

namespace Engine
{
	class ColliderComponent;

	enum class EnemyState
	{
		MoveLeft,
		MoveRight,
		Jump,
		Idle
	};

	class EnemyControllerComponent : public BaseComponent
	{
	public:
		EnemyControllerComponent(const std::shared_ptr<GameObject>& owner,
			std::vector<std::shared_ptr<ColliderComponent>> levelCollision, int width, int height);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		bool IsIntersecting(Rect& other);

		EnemyControllerComponent(const EnemyControllerComponent&) = delete;
		EnemyControllerComponent(EnemyControllerComponent&&) = delete;
		EnemyControllerComponent& operator= (const EnemyControllerComponent&) = delete;
		EnemyControllerComponent& operator= (const EnemyControllerComponent&&) = delete;

	private:
		std::vector<std::shared_ptr<ColliderComponent>> m_LevelCollision{};
		EnemyState m_CurrentState{};
		float m_Speed{ 100.f };
		FVector2 m_Velocity{};
		FVector2 m_Acceleration{ 0.f, 981.f };
		int m_Width{};
		int m_Height{};
		float m_JumpCooldown{ 0.f };

		void HandleMovement(bool isMovingLeft, float deltaTime);
		void ApplyGravity(std::shared_ptr<Transform> transform, float deltaTime);
		bool IsIntersecting(int x, int y);
		bool IsTouchingGround();

	};
}
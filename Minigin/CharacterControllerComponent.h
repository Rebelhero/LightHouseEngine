#pragma once
#include "BaseComponent.h"
#include "FVector2.h"
#include "Transform.h"
#include "Rect.h"

#pragma warning(disable:26812)	//disable doesn't work? Warning shouldn't be shown anyways, CharacterState is an enum class
class Command;

namespace Engine
{
	class ColliderComponent;
	class EnemyControllerComponent;

	enum class CharacterState
	{
		MoveLeft,
		MoveRight,
		Jump,
		Shoot,
		Idle
	};

	class CharacterControllerComponent : public BaseComponent
	{
	public:
		CharacterControllerComponent(const std::shared_ptr<GameObject>& owner, int playerID,
			std::vector<std::shared_ptr<ColliderComponent>> levelCollision,
			std::vector<std::shared_ptr<EnemyControllerComponent>> enemies, int width, int height);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		CharacterControllerComponent(const CharacterControllerComponent&) = delete;
		CharacterControllerComponent(CharacterControllerComponent&&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&&) = delete;

	private:
		int m_PlayerID{};
		std::vector<std::unique_ptr<Command>> m_Commands{};
		std::vector<std::shared_ptr<ColliderComponent>> m_LevelCollision{};
		std::vector<std::shared_ptr<EnemyControllerComponent>> m_Enemies{};
		CharacterState m_OldState{};
		CharacterState m_CurrentState{};
		float m_Speed{ 100.f };
		FVector2 m_Velocity{};
		FVector2 m_Acceleration{ 0.f, 981.f };
		int m_Width{};
		int m_Height{};
		float m_JumpCooldown{ 0.f };
		int m_Lives{ 4 };
		float m_InvincibilityTime{ 0.f };

		void HandleInput();
		void HandleMovement(bool isMovingLeft, float deltaTime);
		void ApplyGravity(std::shared_ptr<Transform> transform, float deltaTime);
		bool IsIntersecting(int x, int y);
		bool IsIntersectingWithEnemies();
		bool IsTouchingGround();

	};
}
#pragma warning(default:26812)
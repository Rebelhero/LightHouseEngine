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
	class BoulderComponent;
	class GameObject;

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
		CharacterControllerComponent(const std::shared_ptr<GameObject>& owner, int playerID, int playerCount, int width, int height,
			std::vector<std::shared_ptr<ColliderComponent>> levelCollision,
			std::shared_ptr<std::vector<std::shared_ptr<EnemyControllerComponent>>> enemies,
			std::shared_ptr<std::vector<std::shared_ptr<Engine::GameObject>>> boulders);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		CharacterControllerComponent(const CharacterControllerComponent&) = delete;
		CharacterControllerComponent(CharacterControllerComponent&&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&&) = delete;

	private:
		int m_PlayerID{};
		int m_PlayerCount{};
		std::vector<std::unique_ptr<Command>> m_Commands{};
		std::vector<std::shared_ptr<ColliderComponent>> m_LevelCollision{};
		std::shared_ptr<std::vector<std::shared_ptr<EnemyControllerComponent>>> m_Enemies{};
		std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_Boulders{};
		std::vector< std::shared_ptr<GameObject>> m_Bubbles{};
		CharacterState m_OldState{};
		CharacterState m_CurrentState{};
		float m_Speed{ 100.f };
		FVector2 m_SpawnLocation{};
		FVector2 m_Velocity{};
		FVector2 m_Acceleration{ 0.f, 981.f };
		int m_Width{};
		int m_Height{};
		float m_JumpCooldown{ 0.f };
		int m_Lives{ 4 };
		float m_InvincibilityTime{ 0.f };
		float m_BulletCooldown{ 0.f };
		bool m_GotHit{ false };

		void HandleInput();
		void HandleMovement(bool isMovingLeft, float deltaTime);
		void ApplyGravity(std::shared_ptr<Transform> transform, float deltaTime);
		void UpdateBubbles();
		void CheckBoulderCollision();
		void CheckEnemies();
		bool IsIntersecting(int x, int y);
		bool IsIntersectingWithEnemies();
		bool IsTouchingGround();

	};
}
#pragma warning(default:26812)
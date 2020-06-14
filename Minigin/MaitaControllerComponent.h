#pragma once
#include "EnemyControllerComponent.h"
#include "FVector2.h"
#include "Transform.h"
#include "Rect.h"

class Command;

namespace Engine
{
	class ColliderComponent;
	class GameObject;
	class BoulderComponent;

	class MaitaControllerComponent : public EnemyControllerComponent
	{
	public:
		MaitaControllerComponent(const std::shared_ptr<GameObject>& owner,
			std::vector<std::shared_ptr<ColliderComponent>> levelCollision,
			std::shared_ptr<std::vector<std::shared_ptr<Engine::GameObject>>> boulders, int width, int height);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		std::weak_ptr<GameObject> GetOwner() override;
		bool IsIntersecting(Rect& other) override;
		bool IsFrozen() override;
		void Trap() override;

		MaitaControllerComponent(const MaitaControllerComponent&) = delete;
		MaitaControllerComponent(MaitaControllerComponent&&) = delete;
		MaitaControllerComponent& operator= (const MaitaControllerComponent&) = delete;
		MaitaControllerComponent& operator= (const MaitaControllerComponent&&) = delete;

	private:
		float m_BoulderCooldown{ 0.f };
		std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_Boulders{};

		void CheckBoulders();
	};
}
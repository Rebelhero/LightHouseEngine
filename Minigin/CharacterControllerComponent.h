#pragma once
#include "BaseComponent.h"
#include "Commands.h"

namespace Engine
{
	class CharacterControllerComponent : public BaseComponent
	{
	public:
		CharacterControllerComponent(const std::shared_ptr<GameObject>& owner, short playerID);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		CharacterControllerComponent(const CharacterControllerComponent&) = delete;
		CharacterControllerComponent(CharacterControllerComponent&&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&) = delete;
		CharacterControllerComponent& operator= (const CharacterControllerComponent&&) = delete;

	private:
		short m_PlayerID{};
		std::vector<std::unique_ptr<Command>> m_Commands{};
	};
}

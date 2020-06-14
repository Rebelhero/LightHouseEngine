#pragma once
#include "BaseComponent.h"
#include <string>

class Command;

namespace Engine
{

	class MenuSelectComponent : public BaseComponent
	{
	public:
		MenuSelectComponent(const std::shared_ptr<GameObject>& owner);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		MenuSelectComponent(const MenuSelectComponent&) = delete;
		MenuSelectComponent(MenuSelectComponent&&) = delete;
		MenuSelectComponent& operator= (const MenuSelectComponent&) = delete;
		MenuSelectComponent& operator= (const MenuSelectComponent&&) = delete;

	private:
	};
}


#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class Font;
	class FPSCounterComponent : public BaseComponent
	{
	public:
		FPSCounterComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<Font>& font);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		FPSCounterComponent(const FPSCounterComponent&) = delete;
		FPSCounterComponent(FPSCounterComponent&&) = delete;
		FPSCounterComponent& operator= (const FPSCounterComponent&) = delete;
		FPSCounterComponent& operator= (const FPSCounterComponent&&) = delete;

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;

		int m_FrameCount;
		float m_PassedTime;
	};
}


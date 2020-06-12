#include "LightHousePCH.h"
#include "FPSCounterComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Font.h"
#include "InputManager.h"

Engine::FPSCounterComponent::FPSCounterComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<Font>& font)
	: BaseComponent(owner)
	, m_FrameCount{}
	, m_PassedTime{}
	, m_pTextComponent{ std::make_shared<TextComponent>(owner, "fps", font) }
{
}

void Engine::FPSCounterComponent::Start()
{
	m_pTextComponent->Start();
}

void Engine::FPSCounterComponent::Update(float deltaTime)
{
	m_FrameCount++;	//gets executed once per frame
	m_PassedTime += deltaTime;

	if (m_PassedTime > 1.f)	//one second has passed
	{
		m_pTextComponent->SetText(std::to_string(m_FrameCount));
		m_FrameCount = 0;
		m_PassedTime = 0.f;
	}

	m_pTextComponent->Update(deltaTime);
}

void Engine::FPSCounterComponent::Render()
{
	m_pTextComponent->Render();
}

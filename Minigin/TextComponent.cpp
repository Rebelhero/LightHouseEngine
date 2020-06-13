#include "LightHousePCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

Engine::TextComponent::TextComponent(const std::shared_ptr<GameObject>& owner, const std::string& text, const std::shared_ptr<Font>& font)
	: BaseComponent(owner)
	, m_pTransform{ m_pOwner.lock()->GetTransform() }
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
{
}

void Engine::TextComponent::Start()
{
}

void Engine::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void Engine::TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void Engine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

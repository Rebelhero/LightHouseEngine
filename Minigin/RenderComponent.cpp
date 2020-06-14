#include "LightHousePCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include <SDL.h>
#include "Texture2D.h"

Engine::RenderComponent::RenderComponent(const std::shared_ptr<GameObject>& owner, std::shared_ptr<Texture2D> texture,
	const Rect& srcRect, int offsetX, int offsetY, int dstWidth, int dstHeight)
	: BaseComponent(owner)
	, m_pTransform{ m_pOwner.lock()->GetTransform() }
	, m_SrcRect{ srcRect }
	, m_OffsetX{ offsetX }
	, m_OffsetY{ offsetY }
	, m_DstWidth{ dstWidth }
	, m_DstHeight{ dstHeight }
	, m_Texture{ texture }
{
	//m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	if (!m_Texture)
		std::cout << "Error loading texture " << "\n";

	if (srcRect.width == 0 || srcRect.height == 0)
		SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_SrcRect.width, &m_SrcRect.height);	//get width and height from texture

	if (m_DstWidth == 0 || m_DstHeight == 0)
	{
		m_DstWidth = m_SrcRect.width;
		m_DstHeight = m_SrcRect.height;
	}
}

void Engine::RenderComponent::Start()
{
}

void Engine::RenderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Engine::RenderComponent::Render()
{
	Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, m_pTransform->GetPosition().x + m_OffsetX,
		m_pTransform->GetPosition().y + m_OffsetY, (float)m_DstWidth, (float)m_DstHeight);
}
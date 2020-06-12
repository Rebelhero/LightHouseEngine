#include "LightHousePCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void Engine::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Engine::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Engine::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Engine::Renderer::RenderTexture(const Texture2D& texture, const float dstX, const float dstY) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Engine::Renderer::RenderTexture(const Texture2D& texture, const float dstX, const float dstY, const float dstWidth, const float dstHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(dstWidth);
	dst.h = static_cast<int>(dstHeight);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Engine::Renderer::RenderTexture(const Texture2D& texture, const Rect& srcRect, const float dstX, const float dstY, 
	const float dstWidth, const float dstHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(dstWidth);
	dst.h = static_cast<int>(dstHeight);
	SDL_Rect src;
	src.x = srcRect.x;
	src.y = srcRect.y;
	src.w = srcRect.width;
	src.h = srcRect.height;

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}
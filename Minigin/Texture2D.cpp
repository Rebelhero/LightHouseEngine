#include "LightHousePCH.h"
#include "Texture2D.h"
#include <SDL.h>

Engine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Engine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Engine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}

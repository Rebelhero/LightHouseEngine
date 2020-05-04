#if _DEBUG
#include <vld.h>
#endif

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "LightHousePCH.h"
#include "MainGame.h"

int main(int, char* [])
{
	MainGame mainGame{};
	mainGame.Run();

	return 0;
}
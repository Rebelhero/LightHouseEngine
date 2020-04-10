#if _DEBUG
#include <vld.h>
#endif

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "LightHousePCH.h"
#include "LightHouse.h"

int main(int, char* [])
{
	dae::LightHouse engine{ 0.0167f };
	engine.Run();

	return 0;
}
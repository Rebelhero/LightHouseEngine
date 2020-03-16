#include "LightHousePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//visual leak detector is commented out because it crashes on my machine
#include <vld.h>
#endif

#include "SDL.h"
#include "LightHouse.h"

int main(int, char*[]) {
	dae::LightHouse engine{ 0.0167f };
	engine.Run();
    return 0;
}
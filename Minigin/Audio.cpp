#include "LightHousePCH.h"
#include "Audio.h"

void NullAudio::Play()
{
	std::cout << "NullAudio: PlaySound" << "\n";
}

void NullAudio::StopAll()
{
	std::cout << "NullAudio: StopSounds" << "\n";
}
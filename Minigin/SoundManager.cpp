#include "LightHousePCH.h"
#include "SoundManager.h"

Audio* Engine::SoundManager::m_pAudioService{};
NullAudio Engine::SoundManager::m_DefaultAudioService{};
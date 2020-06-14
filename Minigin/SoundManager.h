#pragma once
#include "Audio.h"

namespace Engine
{
	class SoundManager
	{
	public:
		static void Init() { m_pAudioService = &m_DefaultAudioService; }
		static Audio& GetAudio() { return *m_pAudioService; }
		static void RegisterAudioService(Audio* service)
		{
			m_pAudioService = (service == nullptr) ? &m_DefaultAudioService : service;
		}

	private:
		static Audio* m_pAudioService;
		static NullAudio m_DefaultAudioService;
	};
}
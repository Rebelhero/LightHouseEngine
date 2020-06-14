#pragma once

class Audio
{
public:
	virtual ~Audio() = default;
	virtual void Play() = 0;
	virtual void StopAll() = 0;
};

class NullAudio final : public Audio
{
public:
	void Play() override;
	void StopAll() override;
};
#pragma once
#include "Scene.h"

class MainScene final : public Engine::Scene
{
public:
	explicit MainScene(const std::string& name, int windowScale = 1);

	virtual void Start() override;

private:
	int m_WindowScale;

	void WriteLevel01File();
	void AddLevel01Layout();
};
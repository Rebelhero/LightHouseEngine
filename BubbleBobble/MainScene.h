#pragma once
#include "Scene.h"

class MainScene final : public Engine::Scene
{
public:
	explicit MainScene(const std::string& name);

	virtual void Start() override;
};
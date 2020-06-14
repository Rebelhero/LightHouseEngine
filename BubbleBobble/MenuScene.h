#pragma once
#include "Scene.h"
#include <string>

namespace Engine
{
	class ColliderComponent;
	class EnemyControllerComponent;
	class BoulderComponent;
	class GameObject;
}

class MenuScene final : public Engine::Scene
{
public:
	explicit MenuScene(const std::string& name, int windowScale = 1);

	virtual void Start() override;

private:
	int m_WindowScale;
};
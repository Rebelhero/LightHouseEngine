#pragma once
#include "Scene.h"

namespace Engine
{
	class ColliderComponent;
	class EnemyControllerComponent;
}

class MainScene final : public Engine::Scene
{
public:
	explicit MainScene(const std::string& name, int windowScale = 1);

	virtual void Start() override;

private:
	int m_WindowScale;
	std::vector<std::shared_ptr<Engine::ColliderComponent>> m_LevelColliders{};
	std::shared_ptr<std::vector<std::shared_ptr<Engine::EnemyControllerComponent>>> m_Enemies{};

	void AddEnemies();
	void WriteLevel01File();
	void AddLevel01Layout();
	void AddLevelCollision();
};
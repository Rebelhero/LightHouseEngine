#pragma once
#include "Singleton.h"

namespace Engine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(const std::shared_ptr<Scene>& scene);
		void ChangeCurrentScene(const std::string& name);

		void Start();
		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		void CheckSceneDuplicate(const std::string& name);

		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pCurrentScene{};
	};
}

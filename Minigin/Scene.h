#pragma once
#include "SceneManager.h"

namespace Engine
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void Add(const std::shared_ptr<SceneObject>& object);
		std::string GetName() const;

	protected:
		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}

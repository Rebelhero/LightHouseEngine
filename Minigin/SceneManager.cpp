#include "LightHousePCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Start()
{
	for (auto& scene : m_Scenes)
		scene->Start();
}

void dae::SceneManager::Update(float deltaTime)
{
	//for(auto& scene : m_Scenes)
	//	scene->Update(deltaTime);

	if (m_pCurrentScene)
		m_pCurrentScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
		scene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName() == name)
			throw std::runtime_error("Could not create new scene " + name + ", a scene with that name already exists!");
	}

	const auto scene = std::shared_ptr<Scene>(new Scene(name));

	if (m_Scenes.empty())
		m_pCurrentScene = scene;

	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::ChangeCurrentScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			m_pCurrentScene = m_Scenes[i];
			return;
		}
	}

	std::cout << "Failed to find scene with the name " << name << "\n";
}

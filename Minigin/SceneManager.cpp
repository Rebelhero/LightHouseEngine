#include "LightHousePCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Engine::SceneManager::Start()
{
	for (auto& scene : m_Scenes)
		scene->Start();
}

void Engine::SceneManager::Update(float deltaTime)
{
	//for(auto& scene : m_Scenes)
	//	scene->Update(deltaTime);

	if (m_pCurrentScene)
		m_pCurrentScene->Update(deltaTime);
}

void Engine::SceneManager::Render()
{
	//for (const auto& scene : m_Scenes)
		m_pCurrentScene->Render();
}

Engine::Scene& Engine::SceneManager::CreateScene(const std::string& name)
{
	CheckSceneDuplicate(name);

	const auto scene = std::shared_ptr<Scene>(new Scene(name));

	if (m_Scenes.empty())
		m_pCurrentScene = scene;

	m_Scenes.push_back(scene);
	return *scene;
}

void Engine::SceneManager::AddScene(const std::shared_ptr<Scene>& scene)
{
	CheckSceneDuplicate(scene->GetName());

	if (m_Scenes.empty())
		m_pCurrentScene = scene;

	m_Scenes.push_back(scene);
}

std::string& Engine::SceneManager::GetCurrentScene()
{
	std::string name{ m_pCurrentScene->GetName() };
	return name;
}

void Engine::SceneManager::ChangeCurrentScene(const std::string& name)
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

void Engine::SceneManager::CheckSceneDuplicate(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName() == name)
			throw std::runtime_error("Could not create new scene " + name + ", a scene with that name already exists!");
	}
}
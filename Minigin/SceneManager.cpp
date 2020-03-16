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
	for(auto& scene : m_Scenes)
		scene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
		scene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
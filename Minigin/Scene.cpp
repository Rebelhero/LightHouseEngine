#include "LightHousePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Engine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Engine::Scene::Start()
{
	for (auto& object : m_Objects)
		object->Start();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
		object->Update(deltaTime);
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}

std::string Engine::Scene::GetName()
{
	return m_Name;
}


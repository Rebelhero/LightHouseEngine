#include "LightHousePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Start()
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

std::string dae::Scene::GetName() const
{
	return m_Name;
}


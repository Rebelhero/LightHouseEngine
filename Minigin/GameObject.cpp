#include "LightHousePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

Engine::GameObject::GameObject()
	: m_pTransform{std::make_shared<Transform>()}
{
}

Engine::GameObject::~GameObject()
{
}

void Engine::GameObject::Start()
{
	for (auto& component : m_Components)
		component->Start();
}

void Engine::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
		component->Update(deltaTime);
}

void Engine::GameObject::Render() const
{
	for (auto& component : m_Components)
		component->Render();
}

void Engine::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}

void Engine::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_Components.push_back(component);
}

const std::shared_ptr<Engine::Transform> Engine::GameObject::GetTransform()
{
	return m_pTransform;
}

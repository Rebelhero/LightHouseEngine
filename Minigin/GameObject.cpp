#include "LightHousePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	//for (m_Components.size())
	//{

	//}
}

void dae::GameObject::Start()
{
	for (auto& component : m_Components)
		component->Start();
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
		component->Update(deltaTime);
}

void dae::GameObject::Render() const
{
	for (auto& component : m_Components)
		component->Render();
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_Components.push_back(component);
}

const dae::Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}

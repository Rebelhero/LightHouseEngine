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

	for (auto& child : m_Children)
		child->Start();
}

void Engine::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
		component->Update(deltaTime);

	for (auto& child : m_Children)
		child->Update(deltaTime);
}

void Engine::GameObject::Render() const
{
	for (auto& component : m_Components)
		component->Render();

	for (auto& child : m_Children)
		child->Render();
}

void Engine::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}

void Engine::GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
	m_Children.push_back(child);
}

void Engine::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& component)
{
	m_Components.push_back(component);
}

void Engine::GameObject::RemoveComponent(const std::shared_ptr<BaseComponent>& toDelete)
{
	auto iterator = m_Components.begin();

	while (iterator != m_Components.end())
	{
		if (*iterator && toDelete)
		{
			if (*iterator == toDelete)
			{
				iterator = m_Components.erase(iterator);
				//auto component = *iterator;
				//iterator = m_Components.erase(iterator);
				//component.reset();
				//component = component;
			}
			else
				iterator++;
		}
		else
			iterator++;
	}
}

void Engine::GameObject::RemoveChild(const std::shared_ptr<GameObject>& toDelete)
{
	auto iterator = m_Children.begin();

	while (iterator != m_Children.end())
	{
		if (*iterator && toDelete)
		{
			if (*iterator == toDelete)
				iterator = m_Children.erase(iterator);
			else
				iterator++;
		}
		else
			iterator++;
	}
}

const std::shared_ptr<Engine::Transform> Engine::GameObject::GetTransform()
{
	return m_pTransform;
}

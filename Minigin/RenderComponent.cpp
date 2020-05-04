#include "LightHousePCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

Engine::RenderComponent::RenderComponent(const std::shared_ptr<GameObject>& owner, const std::string& filename)
	: BaseComponent(owner)
	, m_Transform{ m_pOwner.lock()->GetTransform() }
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void Engine::RenderComponent::Start()
{
}

void Engine::RenderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Engine::RenderComponent::Render()
{
	Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}

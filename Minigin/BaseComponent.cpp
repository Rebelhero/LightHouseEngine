#include "LightHousePCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(const std::weak_ptr<GameObject>& owner)
{
	m_pOwner = owner;
}

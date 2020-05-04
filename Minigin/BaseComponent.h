#pragma once

namespace Engine
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(const std::weak_ptr<GameObject>& owner);
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	protected:
		std::weak_ptr<GameObject> m_pOwner;
	};
}


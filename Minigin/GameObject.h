#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "RenderComponent.h"

namespace Engine
{
	class GameObject final : public SceneObject
	{
	public:
		void Start() override;
		void Update(float deltaTime) override;
		void Render() const override;

		void SetPosition(float x, float y);
		void AddChild(const std::shared_ptr<GameObject>& child);
		void AddComponent(const std::shared_ptr<BaseComponent>& component);
		void RemoveComponent(const std::shared_ptr<BaseComponent>& toDelete);
		void RemoveChild(const std::shared_ptr<GameObject>& toDelete);
		template<class T> std::shared_ptr<T> GetComponent();
		const std::shared_ptr<Transform> GetTransform();


		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::shared_ptr<Transform> m_pTransform{};
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
		std::vector<std::shared_ptr<GameObject>> m_Children{};
	};

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent()
	{
		for (auto& base : m_Components)
		{
			std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(base);

			if (component)
				return component;
		}

		return nullptr;
	}
}

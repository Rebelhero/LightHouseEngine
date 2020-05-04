#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace Engine
{
	class Texture2D;
	class Transform;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(const std::shared_ptr<GameObject>& owner, const std::string& filename);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator= (const RenderComponent&) = delete;
		RenderComponent& operator= (const RenderComponent&&) = delete;

	private:
		const Transform& m_Transform;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


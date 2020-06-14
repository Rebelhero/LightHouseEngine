#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"
#include "Rect.h"

namespace Engine
{
	class Texture2D;
	class Transform;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(const std::shared_ptr<GameObject>& owner, std::shared_ptr<Texture2D> texture,
			const Rect& srcRect = Rect(), int offsetX = 0, int offsetY = 0, int dstWidth = 0, int dstHeight = 0);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator= (const RenderComponent&) = delete;
		RenderComponent& operator= (const RenderComponent&&) = delete;

	private:
		std::shared_ptr<Transform> m_pTransform;
		std::shared_ptr<Texture2D> m_Texture;
		Rect m_SrcRect;
		int m_OffsetX;
		int m_OffsetY;
		int m_DstWidth;
		int m_DstHeight;
	};
}


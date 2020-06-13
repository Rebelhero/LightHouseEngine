#pragma once
#include "BaseComponent.h"

namespace Engine
{
	class Transform;
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::shared_ptr<GameObject>& owner, const std::string& text, const std::shared_ptr<Font>& font);
		void Start() override;
		void Update(float deltaTime) override;
		void Render() override;

		void SetText(const std::string& text);

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator= (const TextComponent&) = delete;
		TextComponent& operator= (const TextComponent&&) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Transform> m_pTransform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


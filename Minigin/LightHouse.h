#pragma once
struct SDL_Window;
namespace Engine
{
	class LightHouse
	{
	public:
		LightHouse(float tickRate = 0.0167f, int windowScale = 1);	//fps limit, 60fps by default
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		int GetWindowScale();

	private:
		float m_FixedTimeStep; //0.00695f for 144fps, 0.0083f for 120fps, 0.0167f for 60 fps, 0.0333f for 30 fps
		int m_WindowWidth;
		int m_WindowHeight;
		int m_ScaleFactor;
		SDL_Window* m_Window{};
	};
}
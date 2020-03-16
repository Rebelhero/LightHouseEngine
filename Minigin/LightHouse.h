#pragma once
struct SDL_Window;
namespace dae
{
	class LightHouse
	{
	public:
		LightHouse(float tickRate = 0.0167f);	//fps limit, 60fps by default
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		float m_FixedTimeStep; //0.00695f for 144fps, 0.0083f for 120fps, 0.0167f for 60 fps, 0.0333f for 30 fps
		SDL_Window* m_Window{};
	};
}
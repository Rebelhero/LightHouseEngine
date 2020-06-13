#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace Engine
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(int playerID, ControllerButton button) const;
		bool IsPressed(int playerID, DWORD key) const;
	private:
		XINPUT_STATE m_Player1State{};
		XINPUT_STATE m_Player2State{};
		int m_KeyboardPressed{ 0x8000 };
	};

}

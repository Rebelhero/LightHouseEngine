#include "LightHousePCH.h"
#include "InputManager.h"
#include <SDL.h>


bool Engine::InputManager::ProcessInput()
{
	ZeroMemory(&m_Player1State, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_Player1State);	//0 to 3 for the different controller slots, Player 1

	ZeroMemory(&m_Player2State, sizeof(XINPUT_STATE));
	XInputGetState(1, &m_Player2State);	//Player 2

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool Engine::InputManager::IsPressed(int playerID, ControllerButton button) const
{
	//which of the two players are we processing right now?
	XINPUT_STATE m_CurrentState = (playerID == 0) ? m_Player1State : m_Player2State;

	//Controller Input
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DPadUp:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DPadDown:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DPadLeft:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::DPadRight:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	default: return false;
	}
}

bool Engine::InputManager::IsPressed(int playerID, DWORD key) const
{
	UNREFERENCED_PARAMETER(playerID);
	//Keyboard Input
	return GetKeyState(key) & m_KeyboardPressed;
}


#pragma once
#include <iostream>
#include "InputManager.h"
#include "CharacterControllerComponent.h"

class Command
{
public:
	Command(Engine::ControllerButton button, DWORD key)
		: m_ControllerButton{ button }
		, m_KeyboardKey{ key }
	{}
	virtual ~Command() {};
	virtual Engine::ControllerButton GetButton() { return m_ControllerButton; };
	virtual DWORD GetKey() { return m_KeyboardKey; };
	virtual void execute(Engine::CharacterState& state) = 0;

protected:
	Engine::ControllerButton m_ControllerButton;
	DWORD m_KeyboardKey;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(Engine::CharacterState& state) override
	{
		state = Engine::CharacterState::MoveLeft;
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(Engine::CharacterState& state) override
	{
		state = Engine::CharacterState::MoveRight;
	}
};

class JumpCommand : public Command
{
public:
	JumpCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(Engine::CharacterState& state) override
	{
			state = Engine::CharacterState::Jump;
	}
};

class ShootCommand : public Command
{
public:
	ShootCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(Engine::CharacterState& state) override
	{
		state = Engine::CharacterState::Shoot;
	}
};
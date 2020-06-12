#pragma once
#include <iostream>
#include "InputManager.h"

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
	virtual void execute(float deltaTime) = 0;

protected:
	Engine::ControllerButton m_ControllerButton;
	DWORD m_KeyboardKey;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(float deltaTime) override
	{
		std::cout << "MoveLeftCommand" << "\n";
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(float deltaTime) override
	{
		std::cout << "MoveRightCommand" << "\n";
	}
};

class JumpCommand : public Command
{
public:
	JumpCommand(Engine::ControllerButton button, DWORD key) : Command(button, key) {};
	virtual void execute(float deltaTime) override
	{
		std::cout << "JumpCommand" << "\n";
	}
};
#pragma once
#include <iostream>

class Command
{
public:
	virtual ~Command() {};
	virtual void execute() = 0;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() {};
	virtual void execute() override 
	{
		std::cout << "MoveLeftCommand" << "\n";
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand() {};
	virtual void execute() override 
	{
		std::cout << "MoveRightCommand" << "\n";
	}
};

class JumpCommand : public Command
{
public:
	JumpCommand() {};
	virtual void execute() override 
	{
		std::cout << "JumpCommand" << "\n";
	}
};
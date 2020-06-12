#pragma once
#include "IVector2.h"
#include <vector>
#include "Block.h"
#include <string>

class LevelParser
{
public:
	LevelParser(std::string fileName);

	std::vector<Block> ReadLevelFile();

private:
	std::string m_FileName{};
};


#pragma once
#include <vector>
#include "Block.h"
#include <string>

class LevelWriter
{
public:
	LevelWriter(const std::vector<Block>& blocks, std::string fileName);

	void WriteLevelFile();

public:
	std::vector<Block> m_Blocks{};
	std::string m_FileName{};
};


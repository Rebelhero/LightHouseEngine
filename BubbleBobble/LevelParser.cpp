#include "LevelParser.h"
#include <fstream>

LevelParser::LevelParser(std::string fileName)
	: m_FileName{ fileName }
{
}

std::vector<Block> LevelParser::ReadLevelFile()
{
	std::ifstream levelFile;
	levelFile.open(m_FileName, std::ios::in | std::ios::binary);

	Block currentBlock{};
	std::vector<Block> blocks{};

	while (levelFile)
	{
		levelFile.read((char*)&currentBlock.id, sizeof(char));
		levelFile.read((char*)&currentBlock.position.x, sizeof(short));
		levelFile.read((char*)&currentBlock.position.y, sizeof(short));

		if (levelFile.eof())
			break;

		blocks.push_back(currentBlock);
	}

	levelFile.close();
	return blocks;
}

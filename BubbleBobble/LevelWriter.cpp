#include "LevelWriter.h"
#include <fstream>

LevelWriter::LevelWriter(const std::vector<Block>& blocks, std::string fileName)
	: m_Blocks{ blocks }
	, m_FileName{ fileName }
{
}

void LevelWriter::WriteLevelFile()
{
	std::ofstream ofstream;
	ofstream.open(m_FileName, std::ios::out | std::ios::binary);

	for (size_t i = 0; i < m_Blocks.size(); i++)
	{
		unsigned int blockType{ m_Blocks[i].id };
		int positionX{ m_Blocks[i].position.x };
		int positionY{ m_Blocks[i].position.y };
		ofstream.write((const char*)&blockType, sizeof(char));
		ofstream.write((const char*)&positionX, sizeof(int));
		ofstream.write((const char*)&positionY, sizeof(int));
	}

	ofstream.close();
}
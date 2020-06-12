#include "LightHousePCH.h"
#include "MainScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "Rect.h"
#include "LevelWriter.h"
#include "LevelParser.h"

MainScene::MainScene(const std::string& name, int windowScale)
	: Scene(name)
	, m_WindowScale{ windowScale }
{
}

void MainScene::Start()
{
	auto go = std::make_shared<Engine::GameObject>();
	auto background = std::make_shared<Engine::RenderComponent>(go, "background.jpg");
	go->AddComponent(std::move(background));
	Add(go);

	//go = std::make_shared<Engine::GameObject>();
	//auto logo = std::make_shared<Engine::RenderComponent>(go, "logo.png");
	//go->AddComponent(logo);
	//go->SetPosition(216, 180);
	//Add(go);

	//go = std::make_shared<Engine::GameObject>();
	//auto font = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto textComponent = std::make_shared<Engine::TextComponent>(go, "Programming 4 Assignment", font);
	//go->AddComponent(std::move(textComponent));
	//go->SetPosition(80, 20);
	//Add(go);

	//go = std::make_shared<Engine::GameObject>();
	//auto newFont = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//go->AddComponent(std::make_shared<Engine::FPSCounterComponent>(go, newFont));
	//go->SetPosition(20, 30);
	//Add(go);

	//WriteLevel01File();
	AddLevel01Layout();

	//Base Start for every added component
	Scene::Start();
}

void MainScene::WriteLevel01File()
{
	int blockDimension = 8;	//one block equals 8 pixels on the texture
	int blockScaled = blockDimension * m_WindowScale;

	std::vector<Block> levelBlocks{};
	Block block{};
	block.id = 0;
	block.position.x = blockScaled;
	block.position.y = blockScaled;

	//Upper bound
	for (int i = 0; i < 36; i++)
	{
		block.position.x = blockScaled + blockDimension * i;
		levelBlocks.push_back(block);
	}

	block.position.y = blockScaled * 14;

	//Lower bound
	for (int i = 0; i < 36; i++)
	{
		block.position.x = blockScaled + blockDimension * i;
		levelBlocks.push_back(block);
	}

	block.position.x = blockScaled;

	//Left bound
	for (int i = 0; i < 2; i++)
	{
		block.position.x = blockScaled + blockDimension * i;

		for (int j = 0; j < 26; j++)
		{
			block.position.y = blockScaled + blockDimension * j;
			levelBlocks.push_back(block);
		}
	}

	//Right bound
	for (int i = 0; i < 2; i++)
	{
		block.position.x = blockDimension * 36 + blockDimension * i;

		for (int j = 0; j < 26; j++)
		{
			block.position.y = blockScaled + blockDimension * j;
			levelBlocks.push_back(block);
		}
	}

	//Platform Blocks

	//First Line
	block.position.x = blockScaled * 2;
	block.position.y = blockScaled * 5;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	block.position.x = blockScaled * 17;
	block.position.y = blockScaled * 5;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	int lineOrigin{ blockScaled * 5 };

	for (int i = 0; i < 20; i++)
	{
		block.position.x = lineOrigin + blockDimension * i;
		levelBlocks.push_back(block);
	}

	//Second Line
	block.position.x = blockScaled * 2;
	block.position.y = blockScaled * 8;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	block.position.x = blockScaled * 17;
	block.position.y = blockScaled * 8;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	for (int i = 0; i < 20; i++)
	{
		block.position.x = lineOrigin + blockDimension * i;
		levelBlocks.push_back(block);
	}

	//Third Line
	block.position.x = blockScaled * 2;
	block.position.y = blockScaled * 11;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	block.position.x = blockScaled * 17;
	block.position.y = blockScaled * 11;

	for (int i = 0; i < 2; i++)
	{
		block.position.x += blockDimension * i;
		levelBlocks.push_back(block);
	}

	for (int i = 0; i < 20; i++)
	{
		block.position.x = lineOrigin + blockDimension * i;
		levelBlocks.push_back(block);
	}

	LevelWriter levelWriter{ levelBlocks, "../Data/Levels/level01.b" };
	levelWriter.WriteLevelFile();
}

void MainScene::AddLevel01Layout()
{
	std::vector<Block> levelBlocks{};
	LevelParser levelParser{ "../Data/Levels/level01.b" };
	levelBlocks = levelParser.ReadLevelFile();

	auto levelLayoutGO = std::make_shared<Engine::GameObject>();
	levelLayoutGO->SetPosition(0, 0);
	int blockDimension = 8;	//one block equals 8 pixels on the texture
	int blockScaled = blockDimension * m_WindowScale;

	for (size_t i = 0; i < levelBlocks.size(); i++)
	{	
		//TODO: fix  srcRect read, for now it'll only work for the top row blocks
		unsigned int blockSourceX{ levelBlocks[i].id * blockDimension };
		unsigned int blockSourceY{ 0 };
		Rect rect{ (int)blockSourceX, (int)blockSourceY, blockDimension, blockDimension };
		int positionX{ levelBlocks[i].position.x * m_WindowScale };
		int positionY{ levelBlocks[i].position.y * m_WindowScale };

		//add render of block with the dimensions that are read from the level file
		auto block = std::make_shared<Engine::RenderComponent>(levelLayoutGO, "blocks.png", rect, positionX, positionY, blockScaled, blockScaled);
		levelLayoutGO->AddComponent(block);
	}

	Add(levelLayoutGO);
}

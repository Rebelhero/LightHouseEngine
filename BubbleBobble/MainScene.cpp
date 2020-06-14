#include "LightHousePCH.h"
#include "MainScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "Rect.h"
#include "LevelWriter.h"
#include "LevelParser.h"
#include "CharacterControllerComponent.h"
#include "EnemyControllerComponent.h"
#include "MaitaControllerComponent.h"
#include "ColliderComponent.h"
#include "BoulderComponent.h"
#include "SoundManager.h"

MainScene::MainScene(const std::string& name, int windowScale)
	: Scene(name)
	, m_WindowScale{ windowScale }
	, m_Enemies{ std::make_shared<std::vector<std::shared_ptr<Engine::EnemyControllerComponent>>>() }
	, m_Boulders{ std::make_shared<std::vector<std::shared_ptr<Engine::GameObject>>>() }
{
}

void MainScene::Start()
{
	auto go = std::make_shared<Engine::GameObject>();
	auto texture = Engine::ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto background = std::make_shared<Engine::RenderComponent>(go, texture);
	go->AddComponent(std::move(background));
	Add(go);

	//WriteLevel01File();
	AddLevel01Layout();
	AddLevelCollision();
	AddEnemies();

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(100, 410);
	int playerDimension{ 16 };	//pixel size of the sprite
	int playerScaled{ playerDimension * m_WindowScale };
	Rect rect{ 0, 0, playerDimension, playerDimension };
	texture = Engine::ResourceManager::GetInstance().LoadTexture("sprites0.png");
	auto playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, playerScaled, playerScaled);
	go->AddComponent(playerSprite);

	auto characterController = std::make_shared<Engine::CharacterControllerComponent>(go, 0, 1,
		playerScaled, playerScaled, m_LevelColliders, m_Enemies, m_Boulders);
	go->AddComponent(characterController);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto newFont = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(std::make_shared<Engine::FPSCounterComponent>(go, newFont));
	go->SetPosition(20, 30);
	Add(go);

	//Base Start for every added component
	Scene::Start();

	//Service Locator for Audio, didn't get finished
	Engine::SoundManager::RegisterAudioService(nullptr);
	Engine::SoundManager::GetAudio().StopAll();
	Engine::SoundManager::GetAudio().Play();
}

void MainScene::AddEnemies()
{
	auto go = std::make_shared<Engine::GameObject>();
	int enemyDimension{ 16 };	//pixel size of the sprite
	int enemyScaled{ enemyDimension * m_WindowScale };
	Rect rect{ 0, 64, enemyDimension, enemyDimension };
	auto texture = Engine::ResourceManager::GetInstance().LoadTexture("sprites0.png");
	auto playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);

	auto enemyController = std::make_shared<Engine::EnemyControllerComponent>(go, m_LevelColliders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(300, 110);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);
	enemyController = std::make_shared<Engine::EnemyControllerComponent>(go, m_LevelColliders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(350, 110);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);
	enemyController = std::make_shared<Engine::EnemyControllerComponent>(go, m_LevelColliders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(400, 110);
	Add(go);

	rect = Rect(0, 240, enemyDimension, enemyDimension);
	go = std::make_shared<Engine::GameObject>();
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);
	enemyController = std::make_shared<Engine::MaitaControllerComponent>(go, m_LevelColliders, m_Boulders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(200, 110);
	Add(go);
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
	auto texture = Engine::ResourceManager::GetInstance().LoadTexture("blocks.png");

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
		auto block = std::make_shared<Engine::RenderComponent>(levelLayoutGO, texture, rect, positionX, positionY, blockScaled, blockScaled);
		levelLayoutGO->AddComponent(block);
	}

	Add(levelLayoutGO);
}

void MainScene::AddLevelCollision()
{
	auto go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 448);
	auto collision{ std::make_shared<Engine::ColliderComponent>(go, 512, 16) };
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 32);
	collision = std::make_shared<Engine::ColliderComponent>(go, 512, 16);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(32, 32);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 432);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(576, 32);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 432);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 352);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 256);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 160);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(544, 352);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(544, 256);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(544, 160);
	collision = std::make_shared<Engine::ColliderComponent>(go, 32, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(160, 160);
	collision = std::make_shared<Engine::ColliderComponent>(go, 320, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(160, 256);
	collision = std::make_shared<Engine::ColliderComponent>(go, 320, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(160, 352);
	collision = std::make_shared<Engine::ColliderComponent>(go, 320, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);
}

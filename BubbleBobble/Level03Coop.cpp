#include "LightHousePCH.h"
#include "Level03Coop.h"
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

Level03Coop::Level03Coop(const std::string& name, int windowScale)
	: Scene(name)
	, m_WindowScale{ windowScale }
	, m_Enemies{ std::make_shared<std::vector<std::shared_ptr<Engine::EnemyControllerComponent>>>() }
	, m_Boulders{ std::make_shared<std::vector<std::shared_ptr<Engine::GameObject>>>() }
{
}

void Level03Coop::Start()
{
	auto go = std::make_shared<Engine::GameObject>();
	auto texture = Engine::ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto background = std::make_shared<Engine::RenderComponent>(go, texture);
	go->AddComponent(std::move(background));
	Add(go);

	AddLevel03Layout();
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

	auto characterController = std::make_shared<Engine::CharacterControllerComponent>(go, 0, 2,
		playerScaled, playerScaled, m_LevelColliders, m_Enemies, m_Boulders);
	go->AddComponent(characterController);
	Add(go);

	//Player2
	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(200, 410);
	rect = Rect(0, 32, playerDimension, playerDimension);
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, playerScaled, playerScaled);
	go->AddComponent(playerSprite);

	auto character2Controller = std::make_shared<Engine::CharacterControllerComponent>(go, 1, 2,
		playerScaled, playerScaled, m_LevelColliders, m_Enemies, m_Boulders);
	go->AddComponent(character2Controller);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	auto newFont = Engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(std::make_shared<Engine::FPSCounterComponent>(go, newFont));
	go->SetPosition(20, 30);
	Add(go);

	//Base Start for every added component
	Scene::Start();
}

void Level03Coop::AddEnemies()
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
	go->SetPosition(450, 110);
	Add(go);

	rect = Rect(0, 240, enemyDimension, enemyDimension);
	go = std::make_shared<Engine::GameObject>();
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);
	enemyController = std::make_shared<Engine::MaitaControllerComponent>(go, m_LevelColliders, m_Boulders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(350, 110);
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

	rect = Rect(0, 240, enemyDimension, enemyDimension);
	go = std::make_shared<Engine::GameObject>();
	playerSprite = std::make_shared<Engine::RenderComponent>(go, texture, rect, 0, 0, enemyScaled, enemyScaled);
	go->AddComponent(playerSprite);
	enemyController = std::make_shared<Engine::MaitaControllerComponent>(go, m_LevelColliders, m_Boulders, enemyScaled, enemyScaled);
	go->AddComponent(enemyController);
	m_Enemies->push_back(enemyController);
	go->SetPosition(400, 110);
	Add(go);
}

void Level03Coop::AddLevel03Layout()
{
	std::vector<Block> levelBlocks{};
	LevelParser levelParser{ "../Data/Levels/level03.b" };
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

void Level03Coop::AddLevelCollision()
{
	auto go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 448);
	auto collision{ std::make_shared<Engine::ColliderComponent>(go, 208, 16) };
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(352, 448);
	collision = std::make_shared<Engine::ColliderComponent>(go, 224, 16);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 32);
	collision = std::make_shared<Engine::ColliderComponent>(go, 208, 16);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(352, 32);
	collision = std::make_shared<Engine::ColliderComponent>(go, 224, 16);
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
	go->SetPosition(160, 352);
	collision = std::make_shared<Engine::ColliderComponent>(go, 416, 16, true);
	go->AddComponent(collision);
	m_LevelColliders.push_back(collision);
	Add(go);

	go = std::make_shared<Engine::GameObject>();
	go->SetPosition(64, 256);
	collision = std::make_shared<Engine::ColliderComponent>(go, 416, 16, true);
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
	go->SetPosition(160, 160);
	collision = std::make_shared<Engine::ColliderComponent>(go, 416, 16, true);
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

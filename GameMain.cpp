#include "GameMain.h"
#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "Debug.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "TaskManager.h"
#include "SpriteManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

GameMain::GameMain()
{
	gameManager_ = GameManager::GetInstance();
	debug_ = Debug::GetInstance();
	sceneManager_ = SceneManager::GetInstance();
	collisionManager_ = CollisionManager::GetInstance();
	taskManager_ = TaskManager::GetInstance();
	spriteManager_ = SpriteManager::GetInstance();
}

GameMain::~GameMain()
{
	if (gameManager_)
		delete gameManager_;
	if (debug_)
		delete debug_;
	if (sceneManager_)
		delete sceneManager_;
	if (collisionManager_)
		delete collisionManager_;
	if (taskManager_)
		delete taskManager_;
	if (spriteManager_)
		delete spriteManager_;
}

void GameMain::Initialize()
{
	gameManager_->Initialize();
	debug_->Initialize();
	sceneManager_->Initialize();
}

void GameMain::Update()
{
	static bool flag = false;

	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::P))
		flag = !flag;

	if (!flag)
		sceneManager_->Update();

	taskManager_->Run();
}

void GameMain::Render()
{
	sceneManager_->Render();
	debug_->Draw();

	taskManager_->Render();
}

void GameMain::Finalize()
{
	sceneManager_->Finalize();
}

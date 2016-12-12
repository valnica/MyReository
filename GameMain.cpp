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
	//gameManager_ = GameManager::GetInstance();
	debug_ = Debug::GetInstance();
	//sceneManager_ = SceneManager::GetInstance();
	/*collisionManager_ = CollisionManager::GetInstance();*/
	taskManager_ = TaskManager::GetInstance();
	spriteManager_ = SpriteManager::GetInstance();
}

GameMain::~GameMain()
{
	/*if (gameManager_)
		delete gameManager_;*/
	if (debug_)
		delete debug_;
	/*if (sceneManager_)
		delete sceneManager_;*/
	//if (collisionManager_)
	//	delete collisionManager_;
	if (taskManager_)
		delete taskManager_;
	if (spriteManager_)
		delete spriteManager_;
}

void GameMain::Initialize()
{
	GameManager::GetInstance()->Initialize();
	debug_->Initialize();
	SceneManager::GetInstance()->Initialize();
}

void GameMain::Update()
{
	static bool flag = false;

	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::P))
		flag = !flag;

	if (!flag)
		SceneManager::GetInstance()->Update();

	taskManager_->Run();
}

void GameMain::Render()
{
	SceneManager::GetInstance()->Render();
	debug_->Draw();

	taskManager_->Render();
}

void GameMain::Finalize()
{
	SceneManager::GetInstance()->Finalize();
}

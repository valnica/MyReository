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
	taskManager_ = TaskManager::GetInstance();
}

GameMain::~GameMain()
{
	if (taskManager_)
		delete taskManager_;
}

void GameMain::Initialize()
{
	GameManager::GetInstance()->Initialize();
	Debug::GetInstance()->Initialize();
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
	Debug::GetInstance()->Draw();

	taskManager_->Render();
}

void GameMain::Finalize()
{
	SceneManager::GetInstance()->Finalize();
}

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
	:GameBase(this)
{
}

GameMain::~GameMain()
{
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

	TaskManager::GetInstance()->Run();
}

void GameMain::Render()
{
	SceneManager::GetInstance()->Render();
	Debug::GetInstance()->Draw();
	TaskManager::GetInstance()->Render();
}

void GameMain::Finalize()
{
	SceneManager::GetInstance()->Finalize();
}

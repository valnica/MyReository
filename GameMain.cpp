#include "GameMain.h"
#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "Debug.h"

GameMain::GameMain()
{
	gameManager_ = GameManager::GetInstance();
	scene_ = new PlayScene;
	debug_ = Debug::GetInstance();
}

GameMain::~GameMain()
{
	if (gameManager_)
		delete gameManager_;
	if (scene_)
		delete scene_;
	if (debug_)
		delete debug_;
}

void GameMain::Initialize()
{
	gameManager_->Initialize();
	scene_->Initialize();
	debug_->Initialize();
}

void GameMain::Update()
{
	static bool flag = false;

	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::P))
		flag = !flag;

	if(!flag)
	scene_->Update();
}

void GameMain::Render()
{
	scene_->Render();
}

void GameMain::Finalize()
{
	scene_->Finalize();
}

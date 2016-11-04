#include "GameMain.h"
#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"

GameMain::GameMain()
{
	gameManager_ = GameManager::GetInstance();
	scene_ = new PlayScene;
}

GameMain::~GameMain()
{
	if (gameManager_)
		delete gameManager_;
	if (scene_)
		delete scene_;
}

void GameMain::Initialize()
{
	gameManager_->Initialize();
	scene_->Initialize();
}

void GameMain::Update()
{
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

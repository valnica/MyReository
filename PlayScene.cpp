#include "PlayScene.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "ClearMarker.h"

PlayScene::PlayScene()
{
	stage_ = new Stage;
	player_ = GameManager::GetInstance()->GetPlayer();
	cameraController_ = CameraController::GetInstance();
}


PlayScene::~PlayScene()
{
	if (stage_)
		delete stage_;

	if (player_)
		delete player_;
}

void PlayScene::Initialize()
{
	stage_->Initialize();
	player_->SetStage(stage_);
	player_->Initialize();
	cameraController_->Initialize(GameManager::GetInstance()->GetCamera());
}

void PlayScene::Update()
{
	stage_->Update();
	player_->Update();
	cameraController_->Update();
}

void PlayScene::Render()
{
	stage_->Render();
	player_->Render();
}

void PlayScene::Finalize()
{
	stage_->Finalize();
}

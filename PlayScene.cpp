#include "PlayScene.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "ClearMarker.h"
#include "Enemy.h"
#include <SimpleMath.h>
#include "CollisionManager.h"

using namespace DirectX::SimpleMath;

PlayScene::PlayScene()
{
	stage_ = new Stage;
	player_ = GameManager::GetInstance()->GetPlayer();
	cameraController_ = CameraController::GetInstance();
	collisionManager_ = CollisionManager::GetInstance();
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
	
	//“G‚Ìİ’è
	List<Vector3> movePoint;
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	Enemy* enemy = new Enemy;
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	enemy = new Enemy;
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(25.0f, 0.0f, 25.0f));
	movePoint.PushBack(Vector3(25.0f, 0.0f, -25.0f));
	enemy = new Enemy;
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	collisionManager_->Initialize();
}

void PlayScene::Update()
{
	stage_->Update();
	player_->Update();
	cameraController_->Update();
	for (auto it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Update();
	}

	collisionManager_->Update();
}

void PlayScene::Render()
{
	stage_->Render();
	player_->Render();
	for (auto it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Render();
	}
}

void PlayScene::Finalize()
{
	stage_->Finalize();
}

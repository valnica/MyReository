#include "PlayScene.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Marker.h"
#include "Enemy.h"
#include <SimpleMath.h>
#include "CollisionManager.h"
#include "TPSMode.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

PlayScene::PlayScene()
{
	stage_ = new Stage;
	player_ = GameManager::GetInstance()->GetPlayer();
	cameraController_ = new CameraController;// CameraController::GetInstance();
}


PlayScene::~PlayScene()
{
	if (stage_)
		delete stage_;

	auto enemy = enemy_.begin();
	while (enemy != enemy_.end())
	{
		if ((*enemy))
			delete *enemy;

		enemy = enemy_.erase(enemy);
	}

	if (cameraController_)
		delete cameraController_;
}

void PlayScene::Initialize()
{
	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Initialize();

	stage_->Initialize();

	player_->Initialize();
	player_->SetStage(stage_);
	player_->SetPosition(stage_->GetStartPos());
	player_->SetState(new TPSMode);

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
}

void PlayScene::Update()
{
	stage_->Update();
	player_->Update();
	for (auto it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Update();
	}

	cameraController_->Update();
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

	wchar_t flag[9];
	swprintf_s(flag, 9, L"Play");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void PlayScene::Finalize()
{
	stage_->Finalize();
}

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
#include "Character.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	CollisionManager::GetInstance()->Initialize();

	stage_.reset(new Stage);
	stage_->Initialize();

	player_.reset(new Player);
	player_->Initialize(new TPSMode);
	player_->SetPosition(stage_->GetStartPos());

	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetTarget(player_);

	cameraController_.reset(new CameraController);
	cameraController_->Initialize(camera_);
	
	//ìGÇÃê›íË
	List<Vector3> movePoint;
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	std::shared_ptr<Enemy> enemy;
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(25.0f, 0.0f, 25.0f));
	movePoint.PushBack(Vector3(25.0f, 0.0f, -25.0f));
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	enemy_.push_back(enemy);

	//Object3D::SetCamera(camera_);
	Camera::MainCamera(camera_);
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
	CollisionManager::GetInstance()->Update();
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

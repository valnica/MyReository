//////////////////////////////////////////////
// Name : PlayScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
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

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : PlayScene
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
PlayScene::PlayScene()
{
}

//////////////////////////////////////////////
// Name : ~PlayScene
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
PlayScene::~PlayScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void PlayScene::Initialize()
{
	//当たり判定管理クラスの初期化
	CollisionManager::GetInstance()->Initialize();

	//ステージの初期化
	stage_.reset(new Stage);
	stage_->Initialize();

	//プレイヤーの初期化
	std::shared_ptr<Player> player;
	player.reset(new Player);
	player->Initialize(new TPSMode);
	player->SetPosition(stage_->GetStartPos());
	character_.push_back(player);

	//カメラの初期化
	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetTarget(player);

	//カメラ管理クラスの初期化
	cameraController_.reset(new CameraController);
	cameraController_->Initialize(camera_);
	
	//敵の設定
	List<Vector3> movePoint;
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	std::shared_ptr<Enemy> enemy;
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	character_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -25.0f));
	movePoint.PushBack(Vector3(-5.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -5.0f));
	movePoint.PushBack(Vector3(-25.0f, 0.0f, -25.0f));
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	character_.push_back(enemy);

	movePoint.Clear();
	movePoint.PushBack(Vector3(25.0f, 0.0f, 25.0f));
	movePoint.PushBack(Vector3(25.0f, 0.0f, -25.0f));
	enemy.reset(new Enemy);
	enemy->SetMovePoint(movePoint);
	enemy->Initialize();
	character_.push_back(enemy);

	//メインカメラの設定
	Camera::MainCamera(camera_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void PlayScene::Update()
{
	//更新処理
	stage_->Update();
	for (auto it = character_.begin(); it != character_.end(); it++)
	{
		(*it)->Update();
	}

	cameraController_->Update();
	CollisionManager::GetInstance()->Update();
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void PlayScene::Render()
{
	//描画処理
	stage_->Render();
	for (auto it = character_.begin(); it != character_.end(); it++)
	{
		(*it)->Render();
	}

#ifdef DEBUG
	wchar_t flag[9];
	swprintf_s(flag, 9, L"Play");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
#endif
}

//////////////////////////////////////////////
// Name : Finalize
//
// Over View : 終了処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void PlayScene::Finalize()
{
	stage_->Finalize();
}

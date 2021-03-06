//////////////////////////////////////////////
// Name : GameOverScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "GameOverScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
#include "GameOverState.h"
#include "ResultStage.h"
#include "Sprite.h"

#include "Debug.h"

#include "Used\DirectXTK.h"

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : GameOverScene
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameOverScene::GameOverScene()
{
}

//////////////////////////////////////////////
// Name : ~GameOverScene
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameOverScene::~GameOverScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void GameOverScene::Initialize()
{
	//プレイヤーの初期化
	player_.reset(new Player);
	player_->Initialize(GameOverState::GetInstance());
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	//カメラの初期化
	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() + Vector3(0.0f, 1.0f, -5.0f));

	//ステージの初期化
	stage_.reset(new ResultStage);
	stage_->Initialize();

	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\CharData.png", Vector2(WINDOW_W / 7 * 2, WINDOW_H / 2), RECT{ 0,128,96,192 }, true);
	sprite_->SetScale(3.0f);

	//メインカメラに登録
	Camera::MainCamera(camera_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  役割が終わったかの判定
//////////////////////////////////////////////
bool GameOverScene::Update()
{
	//更新処理
	player_->Update();
	camera_->Update();
	stage_->Update();

	//ボタンを押したらシーン切り替え
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}

	return true;
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
void GameOverScene::Render()
{
	//描画処理
	player_->Render();
	stage_->Render();
	sprite_->Draw();

#ifdef DEBUG
	wchar_t flag[10];
	swprintf_s(flag, 10, L"Game Over");
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
void GameOverScene::Finalize()
{
}

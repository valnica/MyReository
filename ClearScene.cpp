//////////////////////////////////////////////
// Name : ClearScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "ClearScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "ClearState.h"
#include "Camera.h"
#include "ResultStage.h"
#include "Sprite.h"

#include "Used\DirectXTK.h"

#include "Debug.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ClearScene
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearScene::ClearScene()
{
}

//////////////////////////////////////////////
// Name : ~ClearScene
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ClearScene::~ClearScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return : 無し 
//////////////////////////////////////////////
void ClearScene::Initialize()
{
	//プレイヤーの初期化
	player_.reset(new Player);
	player_->Initialize(ClearState::GetInstance());
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	//カメラの初期化
	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() +  Vector3(0.0f, 1.0f, -5.0f));

	//ステージの初期化
	stage_.reset(new ResultStage);
	stage_->Initialize();

	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\CharData.png", Vector2(WINDOW_W / 7 * 2, WINDOW_H / 2), RECT{ 0,64,96,128 }, true);
	sprite_->SetScale(3.0f);

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
// Return : 役割が終わったかの判定 
//////////////////////////////////////////////
bool ClearScene::Update()
{
	//更新処理
	player_->Update();
	camera_->Update();
	stage_->Update();

	//左クリックでシーン切り替え
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
// Return : 無し 
//////////////////////////////////////////////
void ClearScene::Render()
{
	//描画処理
	player_->Render();
	stage_->Render();
	sprite_->Draw();

#ifdef DEBUG
	wchar_t flag[9];
	swprintf_s(flag, 9, L"Clear");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));

#endif //DEBUG
}

void ClearScene::Finalize()
{
}

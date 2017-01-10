//////////////////////////////////////////////
// Name : TitleScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "TitleScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Object3D.h"

#include "Debug.h"

#include "Used\DirectXTK.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : TitleScene
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
TitleScene::TitleScene()
	:alpha_(0)
{
}

//////////////////////////////////////////////
// Name : ~TitleScene
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
TitleScene::~TitleScene()
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
void TitleScene::Initialize()
{
	//画像の読み込み
	sprite_[0].reset(new Sprite);
	sprite_[0]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 120.0f), RECT{ 0,0,320,96 }, true);
	sprite_[1].reset(new Sprite);
	sprite_[1]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 320.0f), RECT{ 0,96,192,160 }, true);
	
	//ステージのリセット
	stage_.reset(new Stage);
	stage_->Initialize();

	//カメラの初期化
	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 0.0f, 0.0f));
	camera_->SetUp(Vector3(0.0f, 1.0f, 0.0f));

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
// Return :  役割が終わったかの判定
//////////////////////////////////////////////
bool TitleScene::Update()
{
	//画像の点滅
	alpha_++;
	float alpha = sinf(alpha_ * 0.05f);
	sprite_[1]->SetAlpha(alpha);

	//更新
	stage_->Update();
	camera_->Update();

	Vector3 vec(0.0f, 0.0f, 40.0f);
	static float angle{};
	angle += 0.5f;
	if (angle > 360.0f)
		angle -= 360;
	Matrix rotY = Matrix::CreateRotationY(angle * 3.14f / 180.0f);
	vec = Vector3::Transform(vec, rotY);
	vec.y = 25.0f;

	//視点の設定
	camera_->SetEye(vec);

	//シーン遷移
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::PLAY);
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
void TitleScene::Render()
{
	sprite_[0]->Draw();
	sprite_[1]->Draw();

	stage_->Render();

#ifdef DEBUG
	wchar_t flag[6];
	swprintf_s(flag, 6, L"Title");
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
void TitleScene::Finalize()
{
}
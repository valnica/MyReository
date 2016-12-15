#include "TitleScene.h"
#include "DirectXTK.h"
#include "SceneManager.h"
#include <SimpleMath.h>
#include "Sprite.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Object3D.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;


TitleScene::TitleScene()
	:alpha_(0)
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	sprite_[0].reset(new Sprite);
	sprite_[0]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 120.0f), RECT{ 0,0,320,96 }, true);
	sprite_[1].reset(new Sprite);
	sprite_[1]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 320.0f), RECT{ 0,96,192,160 }, true);
	
	stage_.reset(new Stage);
	stage_->Initialize();

	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 0.0f, 0.0f));
	camera_->SetUp(Vector3(0.0f, 1.0f, 0.0f));

	Object3D::SetCamera(camera_);
	Camera::MainCamera(camera_);
}

void TitleScene::Update()
{
	alpha_++;

	float alpha = sinf(alpha_ * 0.05f);
	sprite_[1]->SetAlpha(alpha);

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

	camera_->SetEye(vec);

	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::PLAY);
	}
}

void TitleScene::Render()
{
	sprite_[0]->Draw();
	sprite_[1]->Draw();

	stage_->Render();

	wchar_t flag[6];
	swprintf_s(flag, 6, L"Title");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void TitleScene::Finalize()
{
}
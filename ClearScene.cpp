#include "ClearScene.h"
#include "SceneManager.h"
#include "DirectXTK.h"
#include "Player.h"
#include "ClearState.h"
#include "Camera.h"
#include "ResultStage.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	player_.reset(new Player);
	player_->Initialize(new ClearState);
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() +  Vector3(0.0f, 1.0f, -5.0f));

	stage_.reset(new ResultStage);
	stage_->Initialize();

	Camera::MainCamera(camera_);
}

void ClearScene::Update()
{
	player_->Update();

	camera_->Update();

	stage_->Update();

	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

void ClearScene::Render()
{
	player_->Render();

	stage_->Render();

	wchar_t flag[9];
	swprintf_s(flag, 9, L"Clear");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void ClearScene::Finalize()
{
}

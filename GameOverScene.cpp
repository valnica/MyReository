#include "GameOverScene.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include "SceneManager.h"
#include <SimpleMath.h>
#include "Player.h"
#include "GameManager.h"
#include "GameOverState.h"
#include "ResultStage.h"

using namespace DirectX::SimpleMath;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	player_.reset(new Player);
	player_->Initialize(new GameOverState);
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() + Vector3(0.0f, 1.0f, -5.0f));

	stage_.reset(new ResultStage);
	stage_->Initialize();

	Camera::MainCamera(camera_);
}

void GameOverScene::Update()
{
	player_->Update();

	camera_->Update();

	stage_->Update();

	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

void GameOverScene::Render()
{
	player_->Render();

	stage_->Render();

	wchar_t flag[10];
	swprintf_s(flag, 10, L"Game Over");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void GameOverScene::Finalize()
{
}

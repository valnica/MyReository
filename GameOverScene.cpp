#include "GameOverScene.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include "SceneManager.h"
#include <SimpleMath.h>
#include "Player.h"
#include "GameManager.h"
#include "GameOverState.h"

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
	player_ = GameManager::GetInstance()->GetPlayer();
	player_->Initialize();
	player_->SetState(new GameOverState);

	camera_ = GameManager::GetInstance()->GetCamera();
	camera_->SetTarget(player_->GetPosition() + Vector3(0.0f,1.0f,0.0f));
	camera_->SetEye(player_->GetPosition() + Vector3(0.0f, 3.0f, -5.0f));
}

void GameOverScene::Update()
{
	player_->Update();

	camera_->Update();

	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

void GameOverScene::Render()
{
	player_->Render();

	wchar_t flag[10];
	swprintf_s(flag, 10, L"Game Over");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void GameOverScene::Finalize()
{
}

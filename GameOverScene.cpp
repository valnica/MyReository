//////////////////////////////////////////////
// Name : GameOverScene
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "GameOverScene.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
#include "GameOverState.h"
#include "ResultStage.h"

#include "Debug.h"

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : GameOverScene
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameOverScene::GameOverScene()
{
}

//////////////////////////////////////////////
// Name : ~GameOverScene
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameOverScene::~GameOverScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ��������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void GameOverScene::Initialize()
{
	//�v���C���[�̏�����
	player_.reset(new Player);
	player_->Initialize(new GameOverState);
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	//�J�����̏�����
	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() + Vector3(0.0f, 1.0f, -5.0f));

	//�X�e�[�W�̏�����
	stage_.reset(new ResultStage);
	stage_->Initialize();

	//���C���J�����ɓo�^
	Camera::MainCamera(camera_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void GameOverScene::Update()
{
	//�X�V����
	player_->Update();
	camera_->Update();
	stage_->Update();

	//�{�^������������V�[���؂�ւ�
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : �`�揈��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void GameOverScene::Render()
{
	//�`�揈��
	player_->Render();
	stage_->Render();

#ifdef DEBUG
	wchar_t flag[10];
	swprintf_s(flag, 10, L"Game Over");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
#endif
}

//////////////////////////////////////////////
// Name : Finalize
//
// Over View : �I������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void GameOverScene::Finalize()
{
}

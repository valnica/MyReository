//////////////////////////////////////////////
// Name : ClearScene
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "ClearScene.h"
#include "SceneManager.h"
#include "DirectXTK.h"
#include "Player.h"
#include "ClearState.h"
#include "Camera.h"
#include "ResultStage.h"
#include "Debug.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ClearScene
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearScene::ClearScene()
{
}

//////////////////////////////////////////////
// Name : ~ClearScene
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearScene::~ClearScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return : ���� 
//////////////////////////////////////////////
void ClearScene::Initialize()
{
	//�v���C���[�̏�����
	player_.reset(new Player);
	player_->Initialize(new ClearState);
	player_->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));

	//�J�����̏�����
	camera_.reset(new Camera((float)WINDOW_H, (float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 1.0f, 0.0f));
	camera_->SetEye(camera_->GetRef() +  Vector3(0.0f, 1.0f, -5.0f));

	//�X�e�[�W�̏�����
	stage_.reset(new ResultStage);
	stage_->Initialize();

	//���C���J�����̐ݒ�
	Camera::MainCamera(camera_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return : ���� 
//////////////////////////////////////////////
void ClearScene::Update()
{
	//�X�V����
	player_->Update();
	camera_->Update();
	stage_->Update();

	//���N���b�N�ŃV�[���؂�ւ�
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
// Return : ���� 
//////////////////////////////////////////////
void ClearScene::Render()
{
	//�`�揈��
	player_->Render();
	stage_->Render();

#ifdef DEBUG
	wchar_t flag[9];
	swprintf_s(flag, 9, L"Clear");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));

#endif //DEBUG
}

void ClearScene::Finalize()
{
}

//////////////////////////////////////////////
// Name : PlayScene
//
// Author : �R�c ����
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
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
PlayScene::PlayScene()
{
}

//////////////////////////////////////////////
// Name : ~PlayScene
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
PlayScene::~PlayScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void PlayScene::Initialize()
{
	//�����蔻��Ǘ��N���X�̏�����
	CollisionManager::GetInstance()->Initialize();

	//�X�e�[�W�̏�����
	stage_.reset(new Stage);
	stage_->Initialize();

	//�v���C���[�̏�����
	std::shared_ptr<Player> player;
	player.reset(new Player);
	player->Initialize(new TPSMode);
	player->SetPosition(stage_->GetStartPos());
	character_.push_back(player);

	//�J�����̏�����
	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetTarget(player);

	//�J�����Ǘ��N���X�̏�����
	cameraController_.reset(new CameraController);
	cameraController_->Initialize(camera_);
	
	//�G�̐ݒ�
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
// Return :  ����
//////////////////////////////////////////////
void PlayScene::Update()
{
	//�X�V����
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
// Over View : �`�揈��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void PlayScene::Render()
{
	//�`�揈��
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
// Over View : �I������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void PlayScene::Finalize()
{
	stage_->Finalize();
}

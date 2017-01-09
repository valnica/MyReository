//////////////////////////////////////////////
// Name : SceneManager
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : SceneManager
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
SceneManager::SceneManager()
{
}

//////////////////////////////////////////////
// Name : ~SceneManager
//
// Over View : ~�f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
SceneManager::~SceneManager()
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
void SceneManager::Initialize()
{
	//������
	now_.reset(new TitleScene);
	now_->Initialize();
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
void SceneManager::Update()
{
	//�J�ڐ悪����΃V�[���J��
	if (next_)
	{
		now_ = next_;
		next_ = nullptr;
		now_->Initialize();
	}

	now_->Update();
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
void SceneManager::Render()
{
	//�`��
	now_->Render();
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
void SceneManager::Finalize()
{
	//�I������
	now_->Finalize();
}

//////////////////////////////////////////////
// Name : ChangeScene
//
// Over View : �V�[���J�ڂ̐ݒ�
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void SceneManager::ChageScene(SceneManager::SCENEID id)
{
	switch (id)
	{
	case SceneManager::SCENEID::TITLE:
		next_.reset(new TitleScene);
		break;

	case SceneManager::SCENEID::PLAY:
		next_.reset(new PlayScene);
		break;

	case SceneManager::SCENEID::CLEAR:
		next_.reset(new ClearScene);
		break;

	case SceneManager::SCENEID::GAMEOVER:
		next_.reset(new GameOverScene);
		break;

	default:
		break;
	}
}
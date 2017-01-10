//////////////////////////////////////////////
// Name : SceneManager
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "FadeIn.h"
#include "FadeOut.h"

#include "Used\DirectXTK.h"

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
	//�t�F�[�h������΃t�F�[�h���ăV�[���J��
	if (!fade_.empty())
	{
		if (!fade_.top()->Update())
		{
			fade_.pop();
		}
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

	if (!fade_.empty())
	{
		fade_.top()->Render();
	}
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
	if (next_)
		return;

	std::shared_ptr<FadeIn> fadeIn;
	fadeIn.reset(new FadeIn);
	fadeIn->Initialize();
	std::shared_ptr<FadeOut> fadeOut;
	fadeOut.reset(new FadeOut);
	fadeOut->Initialize();

	fade_.push(fadeIn);
	fade_.push(fadeOut);

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
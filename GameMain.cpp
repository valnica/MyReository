//////////////////////////////////////////////
// Name : GameMain
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "GameMain.h"
#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "TaskManager.h"
#include "SpriteManager.h"

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : GameMain
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameMain::GameMain()
	:GameBase(this)
{
}

//////////////////////////////////////////////
// Name : ~GameMain
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameMain::~GameMain()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//////////////////////////////////////////////
void GameMain::Initialize()
{
	GameManager::GetInstance()->Initialize();
	SceneManager::GetInstance()->Initialize();
#ifdef DEBUG
	Debug::GetInstance()->Initialize();
#endif //DEBUG
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
void GameMain::Update()
{
	SceneManager::GetInstance()->Update();

	TaskManager::GetInstance()->Run();
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
void GameMain::Render()
{
	SceneManager::GetInstance()->Render();
	TaskManager::GetInstance()->Render();
#ifdef DEBUG
	Debug::GetInstance()->Draw();
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
void GameMain::Finalize()
{
	SceneManager::GetInstance()->Finalize();
}

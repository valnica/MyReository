//////////////////////////////////////////////
// Name : GameMain
//
// Author : 山田 聖弥
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
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameMain::GameMain()
	:GameBase(this)
{
}

//////////////////////////////////////////////
// Name : ~GameMain
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameMain::~GameMain()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
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
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void GameMain::Update()
{
	SceneManager::GetInstance()->Update();

	TaskManager::GetInstance()->Run();
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
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
// Over View : 終了処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void GameMain::Finalize()
{
	SceneManager::GetInstance()->Finalize();
}

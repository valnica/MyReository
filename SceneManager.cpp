//////////////////////////////////////////////
// Name : SceneManager
//
// Author : 山田 聖弥
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
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
SceneManager::SceneManager()
{
}

//////////////////////////////////////////////
// Name : ~SceneManager
//
// Over View : ~デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
SceneManager::~SceneManager()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void SceneManager::Initialize()
{
	//初期化
	now_.reset(new TitleScene);
	now_->Initialize();
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
void SceneManager::Update()
{
	//遷移先があればシーン遷移
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
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void SceneManager::Render()
{
	//描画
	now_->Render();
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
void SceneManager::Finalize()
{
	//終了処理
	now_->Finalize();
}

//////////////////////////////////////////////
// Name : ChangeScene
//
// Over View : シーン遷移の設定
//
// Argument : 無し
//
// Return :  無し
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
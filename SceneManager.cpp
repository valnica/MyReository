//////////////////////////////////////////////
// Name : SceneManager
//
// Author : 山田 聖弥
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
	//フェードがあればフェードしてシーン遷移
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

	if (!fade_.empty())
	{
		fade_.top()->Render();
	}
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
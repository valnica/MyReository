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

SceneManager::SceneManager()
{
	now_ = new TitleScene;
}


SceneManager::~SceneManager()
{
	if (now_)
		delete now_;
}

void SceneManager::Initialize()
{
	now_->Initialize();

	flag = 0;
}

void SceneManager::Update()
{
	if (next_)
	{
		if (now_)
			delete now_;

		now_ = next_;
		next_ = nullptr;
		now_->Initialize();
	}

	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::Delete))
		Initialize();

	if (flag == 0)
		now_->Update();
}

void SceneManager::Render()
{
	now_->Render();
}

void SceneManager::Finalize()
{
	now_->Finalize();
}

void SceneManager::ChageScene(SceneManager::SCENEID id)
{
	switch (id)
	{
	case SceneManager::SCENEID::TITLE:
		next_ = new TitleScene;
		break;

	case SceneManager::SCENEID::PLAY:
		next_ = new PlayScene;
		break;

	case SceneManager::SCENEID::CLEAR:
		next_ = new ClearScene;
		break;

	case SceneManager::SCENEID::GAMEOVER:
		next_ = new GameOverScene;
		break;

	default:
		break;
	}
}
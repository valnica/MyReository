#include "GameOverScene.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include "SceneManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

void GameOverScene::Render()
{
}

void GameOverScene::Finalize()
{
}

#include "ClearScene.h"
#include "SceneManager.h"
#include "DirectXTK.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;


ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{

}

void ClearScene::Update()
{
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::TITLE);
	}
}

void ClearScene::Render()
{
	wchar_t flag[9];
	swprintf_s(flag, 9, L"Clear");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void ClearScene::Finalize()
{
}

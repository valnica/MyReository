#include "TitleScene.h"
#include "DirectXTK.h"
#include "SceneManager.h"
#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::PLAY);
	}
}

void TitleScene::Render()
{
	wchar_t flag[6];
	swprintf_s(flag, 6, L"Title");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
}

void TitleScene::Finalize()
{
}

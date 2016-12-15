#include "Marker.h"
#include <SimpleMath.h>
#include "GameManager.h"
#include "Culling.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

Marker::Marker()
{
}


Marker::~Marker()
{
}

void Marker::Initialize()
{
	marker_.LoadModelFromFile(L"Resources\\cModels\\Marker.cmo");
	marker_.SetTrans(Vector3(0.0f, 1.0f, 0.0f));
	marker_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetScale(Vector3(1.0f, 1.0f, 1.0f));
}

void Marker::Update()
{
	marker_.Calc();
	CollisionManager::GetInstance()->Entry(this);
}

void Marker::Render()
{
	marker_.Draw();

	box_.Draw();

	wchar_t flag[20];
	if (Culling::InView(box_, Camera::MainCamera(), 6, 0.5f, 0.5f))
	{
		swprintf_s(flag, 20, L"In Camera = true");
	}
	else
		swprintf_s(flag, 20, L"In Camera = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 80));
}

void Marker::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	marker_.SetTrans(pos);
	box_.Translation(pos);
}

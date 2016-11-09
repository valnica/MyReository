#include "ClearMarker.h"
#include <SimpleMath.h>
#include "GameManager.h"
#include "Culling.h"

using namespace DirectX::SimpleMath;

ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
}

void ClearMarker::Initialize()
{
	marker_.LoadModelFromFile(L"Resources\\cModels\\Marker.cmo");
	marker_.SetTrans(Vector3(0.0f, 1.0f, 0.0f));
	marker_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetScale(Vector3(1.0f, 1.0f, 1.0f));

	box_.point[0] = Vector3(-0.5f, 0.5f, -0.5f);
	box_.point[1] = Vector3(0.5f, 0.5f, -0.5f);
	box_.point[2] = Vector3(0.5f, 0.5f, 0.5f);
	box_.point[3] = Vector3(-0.5f, 0.5f, 0.5f);
	box_.point[4] = Vector3(-0.5f, -0.5f, -0.5f);
	box_.point[5] = Vector3(0.5f, -0.5f, -0.5f);
	box_.point[6] = Vector3(0.5f, -0.5f, 0.5f);
	box_.point[7] = Vector3(-0.5f, -0.5f, 0.5f);
}

void ClearMarker::Update()
{
	marker_.Calc();
}

void ClearMarker::Render()
{
	marker_.Draw();

	box_.Draw();

	wchar_t flag[20];
	if (Culling::InView(box_, GameManager::GetInstance()->GetCamera(), 6, 0.5f, 0.5f))
	{
		swprintf_s(flag, 20, L"In Camera = true");
	}
	else
		swprintf_s(flag, 20, L"In Camera = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 80));
}

void ClearMarker::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	marker_.SetTrans(pos);
	box_.Translation(pos);
}

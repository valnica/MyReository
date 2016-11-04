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

	/*box_.marker_.LoadModelFromFile(L"Resources\\cModels\\Marker.cmo");
	box_.marker_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	box_.marker_.SetScale(Vector3(0.1f, 0.1f, 0.1f));*/
	box_.point[0] = Vector3(-0.5f, 0.5f, -0.5f);
	box_.point[1] = Vector3(0.5f, 0.5f, -0.5f);
	box_.point[2] = Vector3(-0.5f, 0.5f, 0.5f);
	box_.point[3] = Vector3(0.5f, 0.5f, 0.5f);
	box_.point[4] = Vector3(-0.5f, -0.5f, -0.5f);
	box_.point[5] = Vector3(0.5f, -0.5f, -0.5f);
	box_.point[6] = Vector3(-0.5f, -0.5f, 0.5f);
	box_.point[7] = Vector3(0.5f, -0.5f, 0.5f);
}

void ClearMarker::Update()
{
	marker_.Calc();
}

void ClearMarker::Render()
{
	marker_.Draw();

	/*for (int i = 0; i < 8; i++)
	{
		box_.marker_.SetTrans(box_.point[i] + marker_.GetTrans());
		box_.marker_.Calc();
		box_.marker_.Draw();
	}*/

	/*wchar_t flag[20];
	if (Culling::InCamera(box_, GameManager::GetInstance()->GetCamera(), 6, 0.5f, 0.5f))
	{
		swprintf_s(flag, 20, L"true");
	}
	else
		swprintf_s(flag, 20, L"false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 60));*/
}
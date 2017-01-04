#include "FPSMode.h"
#include "Player.h"
#include "Stage.h"
#include "Marker.h"
#include "Culling.h"
#include "GameManager.h"
#include "Collision.h"
#include "TPSMode.h"
#include "TaskManager.h"
#include "Flash.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

FPSMode::FPSMode()
{
}

FPSMode::~FPSMode()
{
}

State<Player> * FPSMode::Input(Player& player)
{
	if (g_mouseTracker->rightButton == g_mouseTracker->RELEASED)
	{
		return new TPSMode;
	}
	return nullptr;
}

void FPSMode::Update(Player & player)
{
	//左クリックで写真を撮る
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		TaskManager::GetInstance()->Add<Flash>()->Initialize();
		Collision collision;

		if (collision.MarkerInView())
		{
			Stage::SetClearFlag();
		}
	}

	//カメラの移動量取得
	Vector2 amountOfMoment = Vector2((float)g_mouse.x, (float)g_mouse.y);

	float angle = 0;

	angle -= amountOfMoment.x;

	Vector3 rot = player.GetRotate();
	Matrix rotY = Matrix::CreateRotationY(rot.y * 3.14f / 180.0f);

	player.SetRotate(player.GetRotate() + Vector3(0.0f, angle, 0.0f));
	player.SetHeadRotate(player.GetHeadRotate() + Vector3(-amountOfMoment.y, 0.0f, 0.0f));
}
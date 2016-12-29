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

	Vector3 vel = Vector3::Zero;
	float angle = 0;

	if (g_key.W)
		vel += Vector3::Forward;
	if (g_key.S)
		vel += Vector3::Backward;

	angle -= amountOfMoment.x;

	Vector3 rot = player.GetRotate();
	Matrix rotY = Matrix::CreateRotationY(rot.y * 3.14f / 180.0f);

	vel = Vector3::TransformNormal(vel, rotY);

	vel.Normalize();

	player.SetPosition(player.GetPosition() + vel * speed_);
	player.SetRotate(player.GetRotate() + Vector3(0.0f, angle, 0.0f));
	player.SetHeadRotate(player.GetHeadRotate() + Vector3(-amountOfMoment.y, 0.0f, 0.0f));
}
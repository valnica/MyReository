#include "PlayerMove.h"
#include "Player.h"
#include "Stage.h"
#include "ClearMarker.h"
#include "Culling.h"
#include "GameManager.h"

using namespace DirectX::SimpleMath;

PlayerMove::PlayerMove()
{
}


PlayerMove::~PlayerMove()
{
}

State<Player> * PlayerMove::Input(Player& player)
{
	return nullptr;
}

void PlayerMove::Update(Player & player)
{
	if (g_mouseTracker->leftButton && g_mouseTracker->PRESSED)
	{
		if (Culling::InCamera(player.GetStage()->GetClearMarker()->GetBox(), GameManager::GetInstance()->GetCamera(), 6, 0.5f, 0.5f))
			player.GetStage()->SetClearFlag(true);
	}

	Vector2 amountOfMorment = Vector2(g_mouse.x, g_mouse.y);
	amountOfMorment.Normalize();
	amountOfMorment *= 3.0f;
	//Vector3 headRot = player.GetHeadRotate();
	//headRot += Vector3(-amountOfMorment.y, -amountOfMorment.x, 0.0f);
	//player.SetHeadRotate(headRot);

	
	Vector3 vel = Vector3::Zero;
	float angle = 0;

	if (g_key.W)
		vel += Vector3::Forward;
	if (g_key.S)
		vel += Vector3::Backward;
		
	angle -= amountOfMorment.y;

	Vector3 rot = player.GetRotate();
	Matrix rotY = Matrix::CreateRotationY(rot.y * 3.14f / 180.0f);

	vel = Vector3::TransformNormal(vel, rotY);

	vel.Normalize();

	player.SetPosition(player.GetPosition() + vel * speed_);
	player.SetRotate(player.GetRotate() + Vector3(0.0f, angle, 0.0f));
}

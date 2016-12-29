#include "ClearState.h"
#include "Player.h"

using namespace DirectX::SimpleMath;

ClearState::ClearState()
	:angle_(0.0f)
{
}

ClearState::~ClearState()
{
}

State<Player>* ClearState::Input(Player & player)
{
	return nullptr;
}

void ClearState::Update(Player & player)
{
	angle_ += 0.1f;
	float rad = sinf(angle_) * 30;

	player.SetHeadRotate(Vector3(rad, 0.0f, 0.0f));
}
#include "GameOverState.h"
#include "Player.h"


GameOverState::GameOverState()
	:angle_(0.0f)
{
}


GameOverState::~GameOverState()
{
}

State<Player>* GameOverState::Input(Player & player)
{
	return nullptr;
}

void GameOverState::Update(Player & player)
{
	angle_ += 0.1f;
	float rot = sinf(angle_) * 50.0f;

	player.SetHeadRotate(DirectX::SimpleMath::Vector3(-20.0f, rot, 0.0f));
}

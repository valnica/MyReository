#pragma once
#include "State.h"
#include <SimpleMath.h>

class Player;

class PlayerMove :
	public State<Player>
{
private:
	const float speed_ = 0.2f;

public:
	PlayerMove();
	~PlayerMove();

	State* Input(Player& player) override;
	void Update(Player& player) override;
};


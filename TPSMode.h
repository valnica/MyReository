#pragma once

#include "State.h"

class Player;

class TPSMode:public State<Player>
{
private:
	const float speed_ = 0.2f;

public:
	TPSMode();
	~TPSMode();

	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};
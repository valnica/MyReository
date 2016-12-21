#pragma once

#include "State.h"
#include "Singleton.h"

class Player;

class TPSMode:public State<Player>,Singleton<TPSMode>
{
private:
	const float speed_ = 0.2f;

public:
	TPSMode();
	~TPSMode();

	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};
#pragma once

#include "State.h"

class Player;

class ClearState:public State<Player>
{
private:
	float angle_;

public:
	ClearState();
	~ClearState();

	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};
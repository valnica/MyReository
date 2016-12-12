#pragma once

#include "State.h"

class Player;

class GameOverState:public State<Player>
{
private:
	float angle_;

public:
	GameOverState();
	~GameOverState();

	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};


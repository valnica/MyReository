#pragma once
#include "State.h"
#include <SimpleMath.h>

class Player;

class FPSMode :
	public State<Player>
{
private:
	const float speed_ = 0.2f;

public:
	FPSMode();
	~FPSMode();

	State* Input(Player& player) override;
	void Update(Player& player) override;
};


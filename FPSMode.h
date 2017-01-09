//////////////////////////////////////////////
// Name : FPSMode
//
// Author : R“c ¹–í
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include "State.h"
#include <SimpleMath.h>

class Player;

//////////////////////////////////////////////
// Class Name : FPSMode
//
// Over View : åŠÏState
//////////////////////////////////////////////
class FPSMode :
	public State<Player>
{
private:

public:
	FPSMode();
	~FPSMode();

	//StateØ‚è‘Ö‚¦ŠÖ”
	State* Input(Player& player) override;
	void Update(Player& player) override;
};


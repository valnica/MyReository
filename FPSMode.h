//////////////////////////////////////////////
// Name : FPSMode
//
// Author : �R�c ����
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
// Over View : ���State
//////////////////////////////////////////////
class FPSMode :
	public State<Player>
{
private:

public:
	FPSMode();
	~FPSMode();

	//State�؂�ւ��֐�
	State* Input(Player& player) override;
	void Update(Player& player) override;
};


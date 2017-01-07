//////////////////////////////////////////////
// Name : TPSMode
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "State.h"
#include "Singleton.h"

class Player;

//////////////////////////////////////////////
// Class Name : TPSMode
//
// Over View : 客観State
//////////////////////////////////////////////
class TPSMode:public State<Player>,Singleton<TPSMode>
{
private:
	//移動スピード
	const float speed_ = 0.2f;

public:
	TPSMode();
	~TPSMode();

	//State切り替え関数
	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};
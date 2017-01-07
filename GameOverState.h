//////////////////////////////////////////////
// Name : GameOverState
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Player;

//////////////////////////////////////////////
// Class Name : GameOverState
//
// Over View : プレイヤーのゲームオーバーシーンのState
//////////////////////////////////////////////
class GameOverState:public State<Player>
{
private:
	//首を回転させるための変数
	float angle_;

public:
	GameOverState();
	~GameOverState();

	//State切り替え関数
	State<Player>* Input(Player& player) override;
	void Update(Player& player) override;
};


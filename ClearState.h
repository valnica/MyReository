//////////////////////////////////////////////
// Name : ClearState
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Player;

//////////////////////////////////////////////
// Name : ClearState
//
// Over View : プレイヤーのクリアシーンのState
//////////////////////////////////////////////
class ClearState:public State<Player>,public Singleton<ClearState>
{
private:
	//首を回転させるための変数
	float angle_;

public:
	ClearState();
	~ClearState();

	//Stateの切り替え用の関数
	std::shared_ptr<State<Player>> Input(Player& player) override;
	
	void Update(Player& player) override;
};
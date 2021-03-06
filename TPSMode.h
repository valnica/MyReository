//////////////////////////////////////////////
// Name : TPSMode
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "State.h"
#include "Singleton.h"

class Player;

//////////////////////////////////////////////
// Class Name : TPSMode
//
// Over View : �q��State
//////////////////////////////////////////////
class TPSMode:public State<Player>,public Singleton<TPSMode>
{
private:
	//�ړ��X�s�[�h
	const float speed_ = 0.2f;

public:
	TPSMode();
	~TPSMode();

	//State�؂�ւ��֐�
	std::shared_ptr<State<Player>> Input(Player& player) override;
	void Update(Player& player) override;
};
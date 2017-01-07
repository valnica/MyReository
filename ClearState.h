//////////////////////////////////////////////
// Name : ClearState
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Player;

//////////////////////////////////////////////
// Name : ClearState
//
// Over View : �v���C���[�̃N���A�V�[����State
//////////////////////////////////////////////
class ClearState:public State<Player>
{
private:
	//�����]�����邽�߂̕ϐ�
	float angle_;

public:
	ClearState();
	~ClearState();

	//State�̐؂�ւ��p�̊֐�
	State<Player>* Input(Player& player) override;
	
	void Update(Player& player) override;
};
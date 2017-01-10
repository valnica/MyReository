//////////////////////////////////////////////
// Name : GameOverState
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "State.h"

class Player;

//////////////////////////////////////////////
// Class Name : GameOverState
//
// Over View : �v���C���[�̃Q�[���I�[�o�[�V�[����State
//////////////////////////////////////////////
class GameOverState:public State<Player>,public Singleton<GameOverState>
{
private:
	//�����]�����邽�߂̕ϐ�
	float angle_;

public:
	GameOverState();
	~GameOverState();

	//State�؂�ւ��֐�
	std::shared_ptr<State<Player>> Input(Player& player) override;
	void Update(Player& player) override;
};


//////////////////////////////////////////////
// Name : GameBase
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include <memory>
#include <Windows.h>

class Window;

//////////////////////////////////////////////
// Class Name : GameBase
//
// Over View : �Q�[�����񂷂��߂̃N���X
//////////////////////////////////////////////
class GameBase
{
private:
	//�������Q�[���N���X�̕ϐ�
	GameBase* game_;
	
	//�E�B���h�E�N���X
	std::unique_ptr<Window> window_;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
public:
	GameBase();
	GameBase(GameBase* game);
	~GameBase();

	//GameBase�̃��C���֐�
	void Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};


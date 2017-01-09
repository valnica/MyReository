//////////////////////////////////////////////
// Name : Character
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : Camera
//
// Over View : �L�����N�^�[�̊��N���X
//////////////////////////////////////////////
class Character
{
private:

public:
	Character() = default;
	virtual ~Character() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
//////////////////////////////////////////////
// Name : State
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : State
//
// Over View : State�̊��N���X
//////////////////////////////////////////////
template <class T>
class State
{
private:

public:
	State() {};
	virtual ~State() {};

	//State�؂�ւ��N���X
	virtual State<T>* Input(T& data) = 0;
	virtual void Update(T& data) = 0;
};
//////////////////////////////////////////////
// Name : State
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : State
//
// Over View : Stateの基底クラス
//////////////////////////////////////////////
template <class T>
class State
{
private:

public:
	State() {};
	virtual ~State() {};

	//State切り替えクラス
	virtual std::shared_ptr<State<T>> Input(T& data) = 0;
	virtual void Update(T& data) = 0;
};
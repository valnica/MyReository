//////////////////////////////////////////////
// Name : Character
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : Camera
//
// Over View : キャラクターの基底クラス
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
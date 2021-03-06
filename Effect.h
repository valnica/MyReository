//////////////////////////////////////////////
// Name : Effect
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : Camera
//
// Over View : エフェクトの基底クラス
//////////////////////////////////////////////
class Effect
{
public:
	Effect() {};
	virtual ~Effect() {};

	virtual void Initialize() {};
	virtual bool Update() { return true; }
	virtual void Render() {};
};
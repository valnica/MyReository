//////////////////////////////////////////////
// Name : Flash
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include "Effect.h"
#include <memory>

class Sprite;

//////////////////////////////////////////////
// Class Name : Flash
//
// Over View : フラッシュエフェクト
//////////////////////////////////////////////
class Flash:public Effect
{
private:
	//フラッシュ用の画像
	std::unique_ptr<Sprite> sprite_;
	
	//透明度
	float alpha_;

public:
	Flash();
	~Flash();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};


//////////////////////////////////////////////
// Name : ClearFlagInfo
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Effect.h"

#include <memory>

class Sprite;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : クリアフラグ通知用クラス
//////////////////////////////////////////////
class ClearFlagInfo:public Effect
{
private:
	std::shared_ptr<Sprite> sprite_;
	int count_;
	float alpha_;

public:
	ClearFlagInfo();
	~ClearFlagInfo();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};


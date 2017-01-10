//////////////////////////////////////////////
// Name : ClearFlagInfo
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include <memory>
#include "Effect.h"

class Sprite;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : �N���A�t���O�ʒm�p�N���X
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


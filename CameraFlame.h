//////////////////////////////////////////////
// Name : CameraFlame
//
// Author : éRìc êπñÌ
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Effect.h"

#include <memory>

class Sprite;

//////////////////////////////////////////////
// Class Name : CameraFlame
//
// Over View : ÉJÉÅÉâ
//////////////////////////////////////////////
class CameraFlame:public Effect
{
private:
	std::shared_ptr<Sprite> sprite_;
	int count_;

public:
	CameraFlame();
	~CameraFlame();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};


//////////////////////////////////////////////
// Name : FadeOut
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Scene.h"

#include <memory>

class Sprite;

//////////////////////////////////////////////
// Class Name : FadeOut
//
// Over View : フェードアウト
//////////////////////////////////////////////
class FadeOut :public Scene
{
private:
	std::shared_ptr<Sprite> sprite_;
	float alpha_;

public:
	FadeOut();
	~FadeOut();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};


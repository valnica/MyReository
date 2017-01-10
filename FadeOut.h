//////////////////////////////////////////////
// Name : FadeOut
//
// Author : �R�c ����
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
// Over View : �t�F�[�h�A�E�g
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


//////////////////////////////////////////////
// Name : FadeIn
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
// Class Name : FadeIn
//
// Over View : �t�F�[�h�C��
//////////////////////////////////////////////
class FadeIn :
	public Scene
{
private:
	std::shared_ptr<Sprite> sprite_;
	float alpha_;

public:
	FadeIn();
	~FadeIn();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};


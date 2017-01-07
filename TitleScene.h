//////////////////////////////////////////////
// Name : TitleScene
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Scene.h"
#include "Lerp.h"
#include <memory>

class Sprite;
class Stage;
class Camera;

//////////////////////////////////////////////
// Name : TitleScene
//
// Over View : �^�C�g���V�[�����Ǘ�����N���X
//////////////////////////////////////////////
class TitleScene:public Scene
{
private:
	//�^�C�g���V�[���ɕK�v�ȕϐ�
	std::unique_ptr<Sprite> sprite_[2];
	int alpha_;
	std::unique_ptr<Stage> stage_;
	std::shared_ptr<Camera> camera_;

public:
	TitleScene();
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};
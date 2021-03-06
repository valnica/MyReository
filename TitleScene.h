//////////////////////////////////////////////
// Name : TitleScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Scene.h"

#include <memory>

class Sprite;
class Stage;
class Camera;

//////////////////////////////////////////////
// Name : TitleScene
//
// Over View : タイトルシーンを管理するクラス
//////////////////////////////////////////////
class TitleScene:public Scene
{
private:
	//タイトルシーンに必要な変数
	std::unique_ptr<Sprite> sprite_[2];
	int alpha_;
	std::unique_ptr<Stage> stage_;
	std::shared_ptr<Camera> camera_;

public:
	TitleScene();
	~TitleScene();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};
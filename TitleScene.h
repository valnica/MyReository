#pragma once

#include "Scene.h"
#include "Lerp.h"

class Sprite;
class Stage;
class Camera;

class TitleScene:public Scene
{
private:
	Sprite* sprite_[2];
	int alpha_;
	Stage* stage_;
	Camera* camera_;

public:
	TitleScene();
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};
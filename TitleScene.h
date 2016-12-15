#pragma once

#include "Scene.h"
#include "Lerp.h"
#include <memory>

class Sprite;
class Stage;
class Camera;

class TitleScene:public Scene
{
private:
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
#pragma once
#include <memory>

#include "Scene.h"

class Player;
class Camera;

class ClearScene:public Scene
{
private:
	std::shared_ptr<Player> player_;
	std::shared_ptr<Camera> camera_;

public:
	ClearScene();
	~ClearScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


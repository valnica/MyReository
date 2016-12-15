#pragma once
#include "Scene.h"
#include <memory>

class Player;
class Camera;

class GameOverScene:public Scene
{
private:
	std::shared_ptr<Player> player_;
	std::shared_ptr<Camera> camera_;

public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


#pragma once
#include "Scene.h"

class Player;
class Camera;

class GameOverScene:public Scene
{
private:
	Player* player_;
	Camera* camera_;

public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


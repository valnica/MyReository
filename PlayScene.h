#pragma once

#include "Scene.h"

class Stage;
class CameraController;
class Player;
class Enemy;

class PlayScene:public Scene
{
private:
	Stage* stage_;
	CameraController* cameraController_;
	Player* player_;
	Enemy* enemy_;

public:
	PlayScene();
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


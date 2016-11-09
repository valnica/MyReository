#pragma once

#include "Scene.h"
#include <vector>

class Stage;
class CameraController;
class Player;
class Enemy;
class CollisionManager;

class PlayScene:public Scene
{
private:
	Stage* stage_;
	CameraController* cameraController_;
	Player* player_;
	std::vector<Enemy*> enemy_;
	CollisionManager* collisionManager_;

public:
	PlayScene();
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


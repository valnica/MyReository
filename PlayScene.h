#pragma once

#include "Scene.h"
#include <vector>
#include <memory>

class Stage;
class CameraController;
class Player;
class Enemy;
class CollisionManager;
class Character;
class Camera;

class PlayScene:public Scene
{
private:
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<CameraController> cameraController_;
	std::shared_ptr<Player> player_;
	std::vector<std::shared_ptr<Enemy>> enemy_;
	std::shared_ptr<Camera> camera_;

public:
	PlayScene();
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

	void End();
};


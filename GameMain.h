#pragma once

#include <memory>

class GameManager;
class Scene;
class Debug;
class SceneManager;
class CollisionManager;
class TaskManager;
class SpriteManager;

class GameMain
{
private:
	TaskManager* taskManager_;

public:
	GameMain();
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};


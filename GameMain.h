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
	GameManager* gameManager_;
	SceneManager* sceneManager_;
	Debug* debug_;
	//CollisionManager* collisionManager_;
	TaskManager* taskManager_;
	SpriteManager* spriteManager_;

public:
	GameMain();
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};


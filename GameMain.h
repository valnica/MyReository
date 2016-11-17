#pragma once

class GameManager;
class Scene;
class Debug;
class SceneManager;
class CollisionManager;

class GameMain
{
private:
	GameManager* gameManager_;
	SceneManager* sceneManager_;
	Debug* debug_;
	CollisionManager* collisionManager_;

public:
	GameMain();
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};


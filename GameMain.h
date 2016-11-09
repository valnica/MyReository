#pragma once

class GameManager;
class Scene;
class Debug;

class GameMain
{
private:
	GameManager* gameManager_;
	Scene* scene_;
	Debug* debug_;

public:
	GameMain();
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};


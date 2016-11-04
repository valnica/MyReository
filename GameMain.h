#pragma once

class GameManager;
class Scene;

class GameMain
{
private:
	GameManager* gameManager_;
	Scene* scene_;

public:
	GameMain();
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};


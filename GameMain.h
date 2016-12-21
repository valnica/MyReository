#pragma once

#include <memory>
#include "GameBase.h"

class GameManager;
class Scene;
class Debug;
class SceneManager;
class CollisionManager;
class TaskManager;
class SpriteManager;

class GameMain:public GameBase
{
private:

public:
	GameMain();
	~GameMain();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


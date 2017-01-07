//////////////////////////////////////////////
// Name : Camera
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
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

//////////////////////////////////////////////
// Class Name : GameMain
//
// Over View : ゲームのメインクラス
//////////////////////////////////////////////
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


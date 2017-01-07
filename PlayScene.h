//////////////////////////////////////////////
// Name : PlayScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
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

//////////////////////////////////////////////
// Class Name : PlayScene
//
// Over View : プレイシーン管理クラス
//////////////////////////////////////////////
class PlayScene:public Scene
{
private:
	//プレイシーンに必要なクラス
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<CameraController> cameraController_;
	std::vector<std::shared_ptr<Character>> character_;
	std::shared_ptr<Camera> camera_;

public:
	PlayScene();
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;

	//終了通知関数
	void End();
};


//////////////////////////////////////////////
// Name : GameOverScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once
#include "Scene.h"
#include <memory>

class Player;
class Camera;
class ResultStage;

//////////////////////////////////////////////
// Class Name : GameOverScene
//
// Over View : ゲームオーバーシーンを管理するクラス
//////////////////////////////////////////////
class GameOverScene:public Scene
{
private:
	//シーンに必要な変数
	std::shared_ptr<Player> player_;
	std::shared_ptr<Camera> camera_;
	std::shared_ptr<ResultStage> stage_;

public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


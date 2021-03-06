//////////////////////////////////////////////
// Name : ClearScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Scene.h"

#include <memory>

class Player;
class Camera;
class ResultStage;
class Sprite;

//////////////////////////////////////////////
// Class Name : ClearScene
//
// Over View : クリアシーンを管理するクラス
//////////////////////////////////////////////
class ClearScene:public Scene
{
private:
	//シーンに必要な変数
	std::shared_ptr<Player> player_;
	std::shared_ptr<Camera> camera_;
	std::shared_ptr<ResultStage> stage_;
	std::shared_ptr<Sprite> sprite_;

public:
	ClearScene();
	~ClearScene();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};


//////////////////////////////////////////////
// Name : ClearScene
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include <memory>
#include "Scene.h"

class Player;
class Camera;
class ResultStage;

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

public:
	ClearScene();
	~ClearScene();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};


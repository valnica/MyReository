//////////////////////////////////////////////
// Name : GameOverScene
//
// Author : �R�c ����
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
// Class Name : GameOverScene
//
// Over View : �Q�[���I�[�o�[�V�[�����Ǘ�����N���X
//////////////////////////////////////////////
class GameOverScene:public Scene
{
private:
	//�V�[���ɕK�v�ȕϐ�
	std::shared_ptr<Player> player_;
	std::shared_ptr<Camera> camera_;
	std::shared_ptr<ResultStage> stage_;
	std::shared_ptr<Sprite> sprite_;

public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;
	bool Update() override;
	void Render() override;
	void Finalize() override;
};


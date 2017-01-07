//////////////////////////////////////////////
// Name : GameOverScene
//
// Author : �R�c ����
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
// Over View : �Q�[���I�[�o�[�V�[�����Ǘ�����N���X
//////////////////////////////////////////////
class GameOverScene:public Scene
{
private:
	//�V�[���ɕK�v�ȕϐ�
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


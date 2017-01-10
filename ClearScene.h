//////////////////////////////////////////////
// Name : ClearScene
//
// Author : �R�c ����
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
// Over View : �N���A�V�[�����Ǘ�����N���X
//////////////////////////////////////////////
class ClearScene:public Scene
{
private:
	//�V�[���ɕK�v�ȕϐ�
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


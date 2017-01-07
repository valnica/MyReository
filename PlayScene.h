//////////////////////////////////////////////
// Name : PlayScene
//
// Author : �R�c ����
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
// Over View : �v���C�V�[���Ǘ��N���X
//////////////////////////////////////////////
class PlayScene:public Scene
{
private:
	//�v���C�V�[���ɕK�v�ȃN���X
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

	//�I���ʒm�֐�
	void End();
};


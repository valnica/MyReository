//////////////////////////////////////////////
// Name : SceneManager
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

#include <memory>
#include <stack>

class Scene;
class PlayScene;
class FadeOut;

//////////////////////////////////////////////
// Class Name : SceneManager
//
// Over View : �V�[���̊Ǘ��N���X
//////////////////////////////////////////////
class SceneManager :public Singleton<SceneManager>
{
private:
	//���̃V�[��
	std::shared_ptr<Scene> now_;
	
	//���̃V�[��
	std::shared_ptr<Scene> next_;

	//�t�F�[�h�p�̕ϐ�
	std::stack<std::shared_ptr<Scene>> fade_;

	friend class Singleton<SceneManager>;

	friend class FadeOut;
	SceneManager();
public:
	~SceneManager();

	//�V�[���̒�`
	enum class SCENEID
	{
		TITLE,
		PLAY,
		CLEAR,
		GAMEOVER
	};

	void Initialize();
	void Update();
	void Render();
	void Finalize();

	//�V�[���̕ύX
	void ChageScene(SCENEID id);
};


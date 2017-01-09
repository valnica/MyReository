//////////////////////////////////////////////
// Name : SceneManager
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include "Singleton.h"

#include <memory>

class Scene;
class PlayScene;

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

	friend class Singleton<SceneManager>;

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


#pragma once
#include "Singleton.h"

class Scene;
class PlayScene;

class SceneManager :public Singleton<SceneManager>
{
private:
	Scene* now_;
	Scene* next_;

	int flag;

	friend class Singleton<SceneManager>;

	SceneManager();
public:
	~SceneManager();

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

	void ChageScene(SCENEID id);
};


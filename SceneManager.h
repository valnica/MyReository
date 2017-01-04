#pragma once
#include "Singleton.h"

#include <memory>

class Scene;
class PlayScene;

class SceneManager :public Singleton<SceneManager>
{
private:
	std::shared_ptr<Scene> now_;
	std::shared_ptr<Scene> next_;

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


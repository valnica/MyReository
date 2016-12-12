#pragma once

class Scene;
class PlayScene;

class SceneManager
{
private:
	Scene* now_;
	Scene* next_;

	int flag;
	
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

	static SceneManager* GetInstance()
	{
		static SceneManager* instance = nullptr;

		if (!instance)
		{
			instance = new SceneManager;
		}

		return instance;
	}
};


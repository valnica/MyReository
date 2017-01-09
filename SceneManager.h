//////////////////////////////////////////////
// Name : SceneManager
//
// Author : 山田 聖弥
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
// Over View : シーンの管理クラス
//////////////////////////////////////////////
class SceneManager :public Singleton<SceneManager>
{
private:
	//今のシーン
	std::shared_ptr<Scene> now_;
	
	//次のシーン
	std::shared_ptr<Scene> next_;

	friend class Singleton<SceneManager>;

	SceneManager();
public:
	~SceneManager();

	//シーンの定義
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

	//シーンの変更
	void ChageScene(SCENEID id);
};


//////////////////////////////////////////////
// Name : SceneManager
//
// Author : 山田 聖弥
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
// Over View : シーンの管理クラス
//////////////////////////////////////////////
class SceneManager :public Singleton<SceneManager>
{
private:
	//今のシーン
	std::shared_ptr<Scene> now_;
	
	//次のシーン
	std::shared_ptr<Scene> next_;

	//フェード用の変数
	std::stack<std::shared_ptr<Scene>> fade_;

	friend class Singleton<SceneManager>;

	friend class FadeOut;
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


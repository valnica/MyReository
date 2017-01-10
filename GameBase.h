//////////////////////////////////////////////
// Name : GameBase
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include <memory>
#include <Windows.h>

class Window;

//////////////////////////////////////////////
// Class Name : GameBase
//
// Over View : ゲームを回すためのクラス
//////////////////////////////////////////////
class GameBase
{
private:
	//動かくゲームクラスの変数
	GameBase* game_;
	
	//ウィンドウクラス
	std::unique_ptr<Window> window_;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
public:
	GameBase();
	GameBase(GameBase* game);
	~GameBase();

	//GameBaseのメイン関数
	void Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};


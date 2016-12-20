#pragma once

#include <memory>
#include <Windows.h>

class GameMain;
class Window;

class GameBase
{
private:
	GameMain* main_;
	std::unique_ptr<Window> window_;

public:
	GameBase();
	GameBase(GameMain* gameMain);
	~GameBase();

	void Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};


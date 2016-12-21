#pragma once

#include <memory>
#include <Windows.h>

class Window;

class GameBase
{
private:
	GameBase* game_;
	std::unique_ptr<Window> window_;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
public:
	GameBase();
	GameBase(GameBase* game);
	~GameBase();

	void Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};


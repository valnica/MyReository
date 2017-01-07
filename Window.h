//////////////////////////////////////////////
// Name : Window
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include <Windows.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include "Direct3D.h"
#include "DirectXTK.h"

//////////////////////////////////////////////
// Name : Window
//
// Over View : Window管理クラス
//////////////////////////////////////////////
class Window
{
private:
	static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	
	//インスタンスハンドル
	HINSTANCE hInst_;
	
	// ウインドウハンドル
	HWND hWnd_;

public:
	Window();
	~Window();

	bool Initialize();
	void Finalize();

	//Windowの初期化
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//ウィンドウハンドルの取得
	HWND GetWindowHandle();
};


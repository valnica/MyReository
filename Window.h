#pragma once

#include <Windows.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include "Direct3D.h"
#include "DirectXTK.h"

class Window
{
private:
	static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	HINSTANCE hInst_;	// インスタンスハンドル
	HWND hWnd_;	// ウインドウハンドル

public:
	Window();
	~Window();

	bool Initialize();
	void Finalize();

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle();
};


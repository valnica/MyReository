//////////////////////////////////////////////
// Name : Window
//
// Author : �R�c ����
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
// Over View : Window�Ǘ��N���X
//////////////////////////////////////////////
class Window
{
private:
	static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	
	//�C���X�^���X�n���h��
	HINSTANCE hInst_;
	
	// �E�C���h�E�n���h��
	HWND hWnd_;

public:
	Window();
	~Window();

	bool Initialize();
	void Finalize();

	//Window�̏�����
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�E�B���h�E�n���h���̎擾
	HWND GetWindowHandle();
};


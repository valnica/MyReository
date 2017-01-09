//////////////////////////////////////////////
// Name : Window
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Window.h"

using namespace Microsoft::WRL;
using namespace DirectX;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#define _DEBUG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : Window
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Window::Window()
	:hInst_(nullptr),hWnd_(nullptr)
{
}

//////////////////////////////////////////////
// Name : Window
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Window::~Window()
{
}

//////////////////////////////////////////////
// Name : InitWindow
//
// Over View : �E�B���h�E�̏�����
//
// Argument : 
//
// Return : 
//////////////////////////////////////////////
HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// �E�C���h�E�N���X��o�^����
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)NULL);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// �E�C���h�E���쐬����
	hInst_ = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ���E�C���h�E�T�C�Y
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	hWnd_ = CreateWindow(L"WindowClass", L"Code:S", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!hWnd_)
		return E_FAIL;

	// �E�C���h�E�̕\��
	ShowWindow(hWnd_, nCmdShow);

	return S_OK;
}

//////////////////////////////////////////////
// Name : WndProc
//
// Over View : ���b�Z�[�W�̊m�F
//
// Argument : 
//
// Return : 
//////////////////////////////////////////////
LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// �E�C���h�E���j�����ꂽ���b�Z�[�W
	case WM_DESTROY:		
		// WM_QUIT���b�Z�[�W�𑗏o����i���C�����[�v�𔲂���j
		PostQuitMessage(0);	
		break;

	// �E�C���h�E���A�N�e�B�u���A��A�N�e�B�u�����鎞�ɗ��郁�b�Z�[�W
	case WM_ACTIVATEAPP:	
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	// �L�[���͊֌W�̃��b�Z�[�W
	case WM_KEYDOWN:		
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	// �}�E�X�֌W�̃��b�Z�[�W
	case WM_INPUT:			
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	default:
		// �����ŏ������Ȃ����b�Z�[�W��DefWindowProc�֐��ɔC����
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//////////////////////////////////////////////
// Name : GetWindowHandle
//
// Over View : �E�B���h�E�n���h���̎擾
//
// Argument : ����
//
// Return : �E�B���h�E�n���h��
//////////////////////////////////////////////
HWND Window::GetWindowHandle()
{
	return hWnd_;
}

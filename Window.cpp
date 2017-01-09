//////////////////////////////////////////////
// Name : Window
//
// Author : 山田 聖弥
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
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Window::Window()
	:hInst_(nullptr),hWnd_(nullptr)
{
}

//////////////////////////////////////////////
// Name : Window
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Window::~Window()
{
}

//////////////////////////////////////////////
// Name : InitWindow
//
// Over View : ウィンドウの初期化
//
// Argument : 
//
// Return : 
//////////////////////////////////////////////
HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ウインドウクラスを登録する
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

	// ウインドウを作成する
	hInst_ = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ←ウインドウサイズ
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	hWnd_ = CreateWindow(L"WindowClass", L"Code:S", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!hWnd_)
		return E_FAIL;

	// ウインドウの表示
	ShowWindow(hWnd_, nCmdShow);

	return S_OK;
}

//////////////////////////////////////////////
// Name : WndProc
//
// Over View : メッセージの確認
//
// Argument : 
//
// Return : 
//////////////////////////////////////////////
LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// ウインドウが破棄されたメッセージ
	case WM_DESTROY:		
		// WM_QUITメッセージを送出する（メインループを抜ける）
		PostQuitMessage(0);	
		break;

	// ウインドウがアクティブ化、非アクティブ化する時に来るメッセージ
	case WM_ACTIVATEAPP:	
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	// キー入力関係のメッセージ
	case WM_KEYDOWN:		
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	// マウス関係のメッセージ
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
		// 自分で処理しないメッセージはDefWindowProc関数に任せる
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//////////////////////////////////////////////
// Name : GetWindowHandle
//
// Over View : ウィンドウハンドルの取得
//
// Argument : 無し
//
// Return : ウィンドウハンドル
//////////////////////////////////////////////
HWND Window::GetWindowHandle()
{
	return hWnd_;
}

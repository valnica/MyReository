//////////////////////////////////////////////
// Name : GameBase
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "GameBase.h"
#include "GameMain.h"
#include "Window.h"

#include "Debug.h"

#include "Used\ImaseLib\FPSTimer.h"

#include <SimpleMath.h>

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : GameBase
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameBase::GameBase()
{
}

//////////////////////////////////////////////
// Name : GameBase
//
// Over View : コンストラクタ
//
// Argument : GameBaseの派生先のポインタ
//////////////////////////////////////////////
GameBase::GameBase(GameBase * game)
	:game_(game)
{
}

//////////////////////////////////////////////
// Name : ~GameBase
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameBase::~GameBase()
{
}

//////////////////////////////////////////////
// Name : Main
//
// Over View : ゲームのメイン関数
//
// Argument : ゲームを回すのに必要な変数４つ
//
// Return :  無し
//////////////////////////////////////////////
void GameBase::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 1秒間に60フレームで固定する
	ImaseLib::FPSTimer fpsTimer(60);

	window_.reset(new Window);

	// ウインドウの作成
	if (FAILED(window_->InitWindow(hInstance, nCmdShow)))
		return;

	// DirectXデバイスの初期化
	if (FAILED(Direct3D_InitDevice(window_->GetWindowHandle())))
	{
		// 初期化に失敗
		Direct3D_CleanupDevice();
		return;
	}

	// DirectXTK関係の初期化
	DirectXTK_Initialize();

	DirectXTK_SetWindow(window_->GetWindowHandle(), WINDOW_W / 2.0f, WINDOW_H / 2.0f);

	game_->Initialize();

	// メインループ
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		int fps = fpsTimer.GetNowFPS();
#ifdef DEBUG
		wchar_t buf[16];
		swprintf_s(buf, 16, L"fps = %d", fps);
#endif

		// メッセージが来ているか調べる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// メッセージが来ていればウインドウプロシージャへ送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// キー入力やマウス情報の更新
			DirectXTK_UpdateInputState();

			game_->Update();

			// バックバッファのクリア
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// 深度バッファのクリア
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			//---------- ここで描画コマンドを発行する　---------//
			g_spriteBatch->Begin(SpriteSortMode_BackToFront, g_state->NonPremultiplied(), g_state->PointClamp());

			game_->Render();

#ifdef DEBUG
			// fpsの表示
			g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));
#endif

			g_spriteBatch->End();

			// 画面更新を待つ
			fpsTimer.WaitFrame();

			// バックバッファとフロントバッファを入れ替える
			g_pSwapChain->Present(0, 0);

			if (g_keyTracker->IsKeyPressed(Keyboard::Escape))
			{
				PostQuitMessage(0);
				DestroyWindow(window_->GetWindowHandle());
			}
		}
	}

	// DirectXデバイス周りの終了処理
	Direct3D_CleanupDevice();

	game_->Finalize();
}
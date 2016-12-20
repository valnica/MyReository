#include "GameBase.h"
#include "GameMain.h"
#include "ImaseLib\FPSTimer.h"
#include <SimpleMath.h>
#include "Window.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


GameBase::GameBase()
{
}

GameBase::GameBase(GameMain * gameMain)
	:main_(gameMain)
{
}


GameBase::~GameBase()
{
}

void GameBase::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 1�b�Ԃ�60�t���[���ŌŒ肷��
	ImaseLib::FPSTimer fpsTimer(60);

	window_.reset(new Window);

	// �E�C���h�E�̍쐬
	if (FAILED(window_->InitWindow(hInstance, nCmdShow)))
		return;

	// DirectX�f�o�C�X�̏�����
	if (FAILED(Direct3D_InitDevice(window_->GetWindowHandle())))
	{
		// �������Ɏ��s
		Direct3D_CleanupDevice();
		return;
	}

	// DirectXTK�֌W�̏�����
	DirectXTK_Initialize();

	DirectXTK_SetWindow(window_->GetWindowHandle(), WINDOW_W / 2.0f, WINDOW_H / 2.0f);

	main_->Initialize();

	// ���C�����[�v
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		int fps = fpsTimer.GetNowFPS();
		wchar_t buf[16];
		swprintf_s(buf, 16, L"fps = %d", fps);

		// ���b�Z�[�W�����Ă��邩���ׂ�
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// ���b�Z�[�W�����Ă���΃E�C���h�E�v���V�[�W���֑���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �L�[���͂�}�E�X���̍X�V
			DirectXTK_UpdateInputState();

			main_->Update();

			// �o�b�N�o�b�t�@�̃N���A
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// �[�x�o�b�t�@�̃N���A
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			//---------- �����ŕ`��R�}���h�𔭍s����@---------//
			g_spriteBatch->Begin(SpriteSortMode_BackToFront, g_state->NonPremultiplied(), g_state->PointClamp());

			main_->Render();

			// fps�̕\��
			g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));

			wchar_t mousePosX[20];
			swprintf_s(mousePosX, 20, L"mouse_x = %d", g_mouse.x);
			g_spriteFont->DrawString(g_spriteBatch.get(), mousePosX, Vector2(0, 20));

			wchar_t mousePosY[20];
			swprintf_s(mousePosY, 20, L"mouse_y = %d", g_mouse.y);
			g_spriteFont->DrawString(g_spriteBatch.get(), mousePosY, Vector2(0, 40));


			g_spriteBatch->End();

			// ��ʍX�V��҂�
			fpsTimer.WaitFrame();

			// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���
			g_pSwapChain->Present(0, 0);

			if (g_keyTracker->IsKeyPressed(Keyboard::Escape))
			{
				PostQuitMessage(0);
				DestroyWindow(window_->GetWindowHandle());
			}
		}
	}

	// DirectX�f�o�C�X����̏I������
	Direct3D_CleanupDevice();

	main_->Finalize();
}
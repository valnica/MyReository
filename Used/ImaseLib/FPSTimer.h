//--------------------------------------------------------------------------------------
// File: FPSTimer.h
//
// FPS���������N���X
//
// �g�����FWaitFrame�֐��Ńt���[���X�V�̃^�C�~���O�𒲐����܂�
//         �������������������ꍇ�͒�����WaitFrame�֐����甲���܂�
//		   �����̃o�[�W�����͕`��X�L�b�v�Ȃǂ͍l���Ă��܂���
//
// Date: 2015.2.16
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>

namespace ImaseLib
{
	class FPSTimer
	{
	private:

#pragma region
		LARGE_INTEGER m_freq;	// ������\�p�t�H�[�}���X�J�E���^�̎��g��
		int m_fps;				// FPS�i�P�b������̃t���[�����j
		DWORD m_fpsWait;		// fpsWait = 1000 * 0x10000 / fps
		DWORD m_fpsWaitTT;		// fpsWait�̏��������̌덷������ϐ�
		DWORD m_lastDrawTime;	// �Ō�ɕ`�悵������

		// FPS�v���p�ϐ�
		int m_nowFPS;
		int m_frames;
		DWORD m_beforeTime;

		// ���݂̎��Ԃ��擾����
		DWORD GetNowTime();
#pragma endregion

	public:

		// ������FPS�i�P�b�Ԃ�����̃t���[�����j���w�肷��
		FPSTimer(int fps);

		// �ݒ肳��Ă���FPS���擾����
		int GetFPS();

		// FPS��ύX����
		void SetFPS(int fps);

		// ���̃t���[���܂ő҂��߂̊֐�
		void WaitFrame();

		// ���݂�FPS���擾����
		int GetNowFPS();

	};
}

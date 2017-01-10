//--------------------------------------------------------------------------------------
// File: FPSTimer.cpp
//
// FPS���������N���X
//
// �g�����FWaitFrame�֐��Ńt���[���X�V�̃^�C�~���O�𒲐����܂�
//         �������������������ꍇ�͒�����WaitFrame�֐����甲���܂�
//
// �Q�lURL�Fhttp://sourceforge.jp/projects/nyx-lib/scm/svn/blobs/146/Nyx/branches/v4/Nyx/Source/Timer/FPSTimer.cpp
// �Q�l���ЁFWindows �v���t�F�b�V���i�� �Q�[���v���O���~���O
//
// Date: 2015.2.16
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "FPSTimer.h"

using namespace ImaseLib;

FPSTimer::FPSTimer(int fps)
: m_fps(0)
, m_fpsWait(0)
, m_fpsWaitTT(0)
, m_lastDrawTime(0)
, m_nowFPS(0)
, m_frames(0)
{
	// ������\�p�t�H�[�}���X�J�E���^�̎��g�����擾
	QueryPerformanceFrequency(&m_freq); 
	// FPS�̐ݒ�
	SetFPS(fps);
}

int FPSTimer::GetFPS()
{
	return m_fps;
}

void FPSTimer::SetFPS(int fps)
{
	m_fps = fps;
	if (fps == 0)
	{
		m_fpsWait = 0;
	}
	else
	{
		// 0x00010000 ���Pms�ƍl��1/60(16.66ms)��DWORD�^�ŕ\������
		m_fpsWait = 1000 * 0x10000 / fps;
	}
}

// PC�N������̌o�ߎ��Ԃ�Ԃ�(ms)
DWORD FPSTimer::GetNowTime()
{
	if (m_fps == 0) return 0;

	LARGE_INTEGER time;

	QueryPerformanceCounter(&time);
	return (DWORD)((double)(time.QuadPart * 1000) / m_freq.QuadPart);
}

void FPSTimer::WaitFrame()
{
	// fpsWait��0�̏ꍇ�͑҂��Ȃ�
	if (m_fpsWait == 0) return;

	DWORD nowTime = GetNowTime();

	// fpsWaitTT�ɂ͑҂����Ԃ̏����ȉ��̏�񂪓����Ă���
	m_fpsWaitTT = (m_fpsWaitTT & 0xffff) + m_fpsWait;

	// �҂����Ԃ����߂�i0x0000****��ʂQ�o�C�g���������j
	DWORD waitTime = m_fpsWaitTT >> 16;

	// �o�ߎ��ԁi���݂̎��ԁ|�`�悵�����ԁj���Z�o����
	DWORD elapsedTime = nowTime - m_lastDrawTime;

	// �҂����Ԃ��o�ߎ��Ԃ��z���Ă���̂ő҂K�v�͂Ȃ�
	if (elapsedTime >= waitTime)
	{
		// �`�悵�����Ԃ����݂̎��Ԃɂ��Ċ֐��𔲂���
		m_lastDrawTime = nowTime;

		// ���݂�FPS���擾
		if (nowTime - m_beforeTime >= 1000)
		{
			m_beforeTime = nowTime;
			m_nowFPS = m_frames;
			m_frames = 0;
		}
		m_frames++;

		return;
	}

	//////////////////////////////////////////////////////////////
	//	�܂����̃t���[���X�V�܂Ŏ��Ԃ�����̂ő҂��Ƃɂ���	//
	//////////////////////////////////////////////////////////////

	// Sleep�֐��ő҂��Ƃɂ��邪�덷4ms�ȓ��̏ꍇ��Sleep���Ȃ�
	if (waitTime - elapsedTime >= 4)
	{
		Sleep(waitTime - elapsedTime - 3);
	}
	// Sleep�֐��Ő��m�ȑ҂����Ԃ��w��ł��Ȃ��̂ł����ł���Ƀ��[�v���đ҂�
	while (GetNowTime() - m_lastDrawTime < waitTime);

	// waitTime���ԑ҂������Ƃɂ��āA�Ō�ɕ`�悵�����Ԃ��X�V
	m_lastDrawTime += waitTime;

	// ���݂�FPS���擾
	if (nowTime - m_beforeTime >= 1000)
	{
		m_beforeTime = nowTime;
		m_nowFPS = m_frames;
		m_frames = 0;
	}
	m_frames++;

}

// ���݂�FPS�i1�b������̃t���[�����j���擾����
int FPSTimer::GetNowFPS()
{
	return m_nowFPS;
}

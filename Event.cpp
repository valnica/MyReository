//////////////////////////////////////////////
// Class Name : Event
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Event.h"
#include "Stage.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void ClearEvent::Initialize()
{
}

//////////////////////////////////////////////
// Name : Run
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  �N���A�������̔���
//////////////////////////////////////////////
bool ClearEvent::Run()
{
	bool flag = Stage::GetClearFlag();

	if (flag)
	{
		//�I������
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::CLEAR);
	}

	return flag;
}

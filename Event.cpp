//////////////////////////////////////////////
// Class Name : Event
//
// Author : 山田 聖弥
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
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void ClearEvent::Initialize()
{
}

//////////////////////////////////////////////
// Name : Run
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  クリアしたかの判定
//////////////////////////////////////////////
bool ClearEvent::Run()
{
	bool flag = Stage::GetClearFlag();

	if (flag)
	{
		//終了処理
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::CLEAR);
	}

	return flag;
}

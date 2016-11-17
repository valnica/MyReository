#include "Event.h"
#include "Stage.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

void ClearEvent::Initialize(Stage* stage)
{
	stage_ = stage;
}

bool ClearEvent::Run()
{
	bool flag = stage_->GetClearFlag();

	if (flag)
	{
		//I—¹ˆ—
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::CLEAR);
	}

	return flag;
}

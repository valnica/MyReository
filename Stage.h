#pragma once
#include <vector>
#include <SimpleMath.h>
#include "CollisionManager.h"

class LandShape;
class Marker;
class ClearEvent;

class Stage
{
private:
	std::vector<std::shared_ptr<LandShape>> landshapeList_;
	std::shared_ptr<Marker> marker_;
	DirectX::SimpleMath::Vector3 startPos_;
	std::shared_ptr<ClearEvent> clearEvent_;
	
	static bool clearFlag_;

public:
	Stage();
	~Stage();

	void Initialize();
	void Update();
	void Render();
	void Finalize();

	static void SetClearFlag() { clearFlag_ = true; }
	DirectX::SimpleMath::Vector3 GetStartPos() { return startPos_; }
	static bool GetClearFlag() { return clearFlag_; }
};


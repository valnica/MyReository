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
	std::vector<LandShape*> landshapeList_;
	bool clearFlag_;
	Marker* marker_;
	DirectX::SimpleMath::Vector3 startPos_;
	ClearEvent* clearEvent;

public:
	Stage();
	~Stage();

	void Initialize();
	void Update();
	void Render();
	void Finalize();

	Marker* GetClearMarker() { return marker_; }
	void SetClearFlag(bool flag) { clearFlag_ = flag; }
	DirectX::SimpleMath::Vector3 GetStartPos() { return startPos_; }
	bool GetClearFlag() { return clearFlag_; }
};


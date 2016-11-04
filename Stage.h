#pragma once
#include <vector>
#include <SimpleMath.h>

class LandShape;
class ClearMarker;

class Stage
{
private:
	std::vector<LandShape*> landshapeList_;
	bool clearFlag_;
	ClearMarker* marker_;
	DirectX::SimpleMath::Vector3 startPos_;

public:
	Stage();
	~Stage();

	void Initialize();
	void Update();
	void Render();
	void Finalize();

	ClearMarker* GetClearMarker() { return marker_; }
	void SetClearFlag(bool flag) { clearFlag_ = flag; }
	DirectX::SimpleMath::Vector3 GetStartPos() { return startPos_; }
};


#pragma once
#include "CollisionManager.h"
#include <SimpleMath.h>
class Stage;

class Event
{
protected:
	Box box_;

public:
	Event() {};
	virtual ~Event() {};

	virtual void Initialize() {};
	virtual bool Run() = 0 ;
	virtual void Render() {};

	Box GetBox() { return box_; }
};

class ClearEvent :public Event
{
private:
	DirectX::SimpleMath::Vector3 pos_;
	DirectX::SimpleMath::Vector3 scale_;
	Stage* stage_;


public:
	ClearEvent() {};
	~ClearEvent() {};

	void Initialize(Stage* stage);
	bool Run() override;
	void Render()
	{
		box_.Draw();
	}

	void SetPosition(DirectX::SimpleMath::Vector3 pos)
	{
		pos_ = pos;
	}

	void SetScale(DirectX::SimpleMath::Vector3 scale)
	{
		scale_ = scale;
	}

	void SetBox(Box box)
	{
		box_ = box;
		box_.SetScale(scale_);
		box_.Translation(pos_ + DirectX::SimpleMath::Vector3(0.0f, scale_.y / 2.0f, 0.0f));
	}
};
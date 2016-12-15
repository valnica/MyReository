#pragma once
#include "Effect.h"
#include <memory>

class Sprite;

class Flash:public Effect
{
private:
	std::unique_ptr<Sprite> sprite_;
	float alpha_;

public:
	Flash();
	~Flash();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};


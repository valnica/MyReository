#pragma once
#include "Effect.h"

class Sprite;

class Flash:public Effect
{
private:
	Sprite* sprite_;
	float alpha_;

public:
	Flash();
	~Flash();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};


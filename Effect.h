#pragma once


class Effect
{
public:
	Effect() {};
	virtual ~Effect() {};

	virtual void Initialize() {};
	virtual bool Update() { return true; }
	virtual void Render() {};
};
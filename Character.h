#pragma once

class Character
{
private:

public:
	Character() = default;
	virtual ~Character() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
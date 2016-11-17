#pragma once
#include "Scene.h"

class GameOverScene:public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};


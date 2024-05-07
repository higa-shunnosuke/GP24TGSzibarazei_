#pragma once

#include "SceneBase.h"

class Result :public SceneBase
{
private:
	int back_ground;      //îwåiâÊëú
	int score;            //ÉXÉRÉA

public:
	Result();
	virtual ~Result();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();
};


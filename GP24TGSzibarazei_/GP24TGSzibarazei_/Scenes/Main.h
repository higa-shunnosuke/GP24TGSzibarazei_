#pragma once

#include "SceneBase.h"
#include"vector"
#include"string"
#include"../Objects/GameObject.h"

//ステージの大きさ
typedef struct
{
	int STAGE_WIDTH;	//ステージの横幅
	int STAGE_HEIGHT;	//ステージの縦幅
}StageDat;

class Main:public SceneBase
{
private:
	bool Is_pause;		//ポーズ状態か？

public:
	Main();
	~Main();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual eSceneType Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了時処理
	virtual void Finalize() override;
	//現在のシーンを取得
	virtual eSceneType GetNowScene() const override;
	//ステージの大きさを取得
	static StageDat GetStageSiz();
	//ステージのタイプを取得
	static int GetStageType();


private:
	//当たり判定チェック処理(ヒット時)
	void HitCheckObject(GameObject* a, GameObject* b);
};


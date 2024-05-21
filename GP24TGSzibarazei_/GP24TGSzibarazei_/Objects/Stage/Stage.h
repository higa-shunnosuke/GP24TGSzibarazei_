#pragma once
#include "../Player/Player.h"
#include"../GameObject.h"

class Stage :public GameObject
{
private:
	int type;			//ステージのタイプ
	Vector2D move;		//移動距離
	Player* player;

public:
	Stage();
	~Stage();

	virtual void Initialize() override;	//初期化処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object,int i) override;
	//位置情報取得処理
	virtual Vector2D GetLocation() const override;
	//大きさ取得処理
	virtual Vector2D Getscale() const override;
	//位置情報変更処理
	virtual void SetLocation(const Vector2D& location) override;

	static int GetStage(int i,int j);
	static void SetStage();

private:
};


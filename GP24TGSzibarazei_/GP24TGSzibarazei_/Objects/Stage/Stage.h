#pragma once
#include"../GameObject.h"

class Stage :public GameObject
{
private:
	Vector2D move;		//移動距離

	unsigned int color;	//ブロックの色


public:
	Stage();
	~Stage();

	virtual void Initialize(int stage_type) override;	//初期化処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	//位置情報取得処理
	virtual Vector2D GetLocation() const override;
	//大きさ取得処理
	virtual Vector2D Getscale() const override;
	//位置情報変更処理
	virtual void SetLocation(const Vector2D& location) override;

	//タイプ取得処理
	virtual int GetType() const override;
	static int GetStage(int i);
	static int SetStage();

private:
};


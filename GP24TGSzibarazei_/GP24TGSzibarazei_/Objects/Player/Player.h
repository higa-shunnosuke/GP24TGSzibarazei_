#pragma once

#include"../GameObject.h"

class Player :public GameObject
{
private:
	int hp;               //体力
	int mp;               //マジックパワー
	int ult_active;       //アルティメット使用可能状態
	int animation[8];			//アニメーション画像
	int animation_count;		//アニメーション時間
	int move_image;             //進行方向に対応する画像の読み込み
	int flip_flag;				//反転フラグ

public:
	Player();
	~Player();

	virtual void Initialize() override;	//初期化処理
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

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimeControl();
	//攻撃処理
	void Atack();

};


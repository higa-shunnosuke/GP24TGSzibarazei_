#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"

class Enemy :public GameObject
{
private:
	int animation[20];			//アニメーション画像
	int animation_count;		//アニメーション時間(アイドリング用)
	int HP;						//HitPoint(体力)
	float AS;					//AtackSpeed(攻撃速度)
	int ATK;					//Attack(攻撃力)
	Vector2D Speed;				//AGL(速度)
	int AL;						//AttackLenge(攻撃範囲)
	int ET;						//EnemyType(敵の種類を選択する)
	bool isBoss;				//この敵がボスかどうかを確認する
	Player* player;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;	//初期化処理
	virtual void Attack();				//攻撃処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処理

	//プレイヤーのポインタを受け取る
	virtual void SetPlayer(class Player* player);
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

};
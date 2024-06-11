#pragma once

#include"Enemy.h"

class Enemy_Attack : public GameObject
{

private:
	int animation[25];			//アニメーション画像
	int anim;
	int animation_count;		//アニメーション時間(アイドリング用)
	float AS;					//AtackSpeed(攻撃速度)
	int ATK;					//Attack(攻撃力)
	Vector2D Speed;				//AGL(速度)
	int AL;						//AttackLenge(攻撃範囲)
	Vector2D location;
	float scale;
public:
	Enemy_Attack();
	~Enemy_Attack();

	virtual void Initialize(int enemy_type) override;	//初期化処理
	virtual void Attack();				//攻撃処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処
	virtual void Movement();

	//エネミーの情報を受け取る
	virtual bool SetEnemy(int ATK,int AL,float AS, Vector2D loc);
	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) ;
	//位置情報取得処理
	virtual Vector2D GetLocation() const ;
	//大きさ取得処理
	virtual Vector2D Getscale() const ;
	//位置情報変更処理
	virtual void SetLocation(const Vector2D& location) ;
	//タイプ取得処理
	virtual int GetType() const override;
};


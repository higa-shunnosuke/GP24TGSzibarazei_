#pragma once

#include"Enemy.h"
#include"../Player/Player.h"
#include"../DeleteClass.h"

class Enemy_Attack : public DeleteClass
{

private:
	class Player* player;
	class Enemy* enemy;
	int animation[20];			//アニメーション画像
	int anim;
	int animation_count;		//アニメーション時間(アイドリング用)
	float AS;					//AtackSpeed(攻撃速度)
	int ATK;					//Attack(攻撃力)
	Vector2D Speed;				//AGL(速度)
	int AL;						//AttackLenge(攻撃範囲)
	float radian;
	bool isHit;
public:
	Enemy_Attack();
	~Enemy_Attack();

	virtual void Initialize(int enemy_type) override;	//初期化処理
	virtual void Attack();				//攻撃処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処
	virtual void Movement();
	virtual void AnimControl();


	//エネミーの情報を受け取る
	virtual bool SetEnemy(int ATK,int AL,float AS, Vector2D loc,Player* p,Enemy* e);
	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	//位置情報取得処理
	virtual Vector2D GetLocation() const override;
	//大きさ取得処理
	virtual Vector2D Getscale() const override;
	////タイプ取得処理
	//virtual int GetType() const override;
};


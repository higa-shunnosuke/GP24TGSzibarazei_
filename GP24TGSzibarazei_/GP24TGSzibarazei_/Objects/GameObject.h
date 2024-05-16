#pragma once

#include"../Utility/Vector2D.h"

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;	//位置情報
	Vector2D scale;		//大きさ
	double radian;		//向き
	int image;			//描画する画像
	int sound;			//再生する音源

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//終了時処理

	//ヒットチェック
	bool HitCheck(const class GameObject* GemeObject)const;
	//当たり判定通知処理(ヒット時)
	virtual void OnHitCollision(GameObject* hit_object,int i);
	//位置情報取得処理
	virtual Vector2D GetLocation() const;
	//大きさ取得処理
	virtual Vector2D Getscale() const;
	//位置情報変更処理
	virtual void SetLocation(const Vector2D& location);
	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;
};


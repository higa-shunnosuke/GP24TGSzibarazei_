#pragma once

//オブジェクトの座標
struct Location
{
	float x;
	float y;
};

//オブジェクトのサイズ
struct Scale
{
	float x;
	float y;
};

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Location location;	//位置情報
	Scale scale;		//大きさ
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

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);
	//位置情報取得処理
	virtual Location GetLocation() const;
	//大きさ取得処理
	virtual Scale Getscale() const;
	//位置情報変更処理
	virtual void SetLocation(const Location& location);


};


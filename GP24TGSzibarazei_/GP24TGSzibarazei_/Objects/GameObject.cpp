#include "GameObject.h"
#include "../Scenes/SceneBase.h"
#include"DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	radian(0.0),
	image(0),
	sound(0)
{

}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize(int type)
{

}

//更新所理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{
	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (scale / 2.0f);
	Vector2D box_collision_upper_right = location + (scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void GameObject::Finalize()
{

}


bool GameObject::HitCheck(const GameObject* gameobject) const
{
	bool ret = false; //返り値

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (scale.x / 2);
	my_y[0] = location.y - (scale.y / 2);
	my_x[1] = my_x[0] + scale.x;
	my_y[1] = my_y[0] + scale.y;

	//相手の当たり判定の範囲の計算
	sub_x[0] = gameobject->GetLocation().x - (gameobject->Getscale().x / 2);
	sub_y[0] = gameobject->GetLocation().y - (gameobject->Getscale().y / 2);
	sub_x[1] = sub_x[0] + gameobject->Getscale().x;
	sub_y[1] = sub_y[0] + gameobject->Getscale().y;

	if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
		&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D GameObject::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void GameObject::SetSceneBase(SceneBase* scenebase)
{
	SB = scenebase;
}

//当たり判定の大きさを取得する
Vector2D GameObject::GetBoxSize() const
{
	return scale;
}

//オブジェクトのタイプを取得する
int GameObject::GetType() const
{
	return type;
}
#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include"DxLib.h"

//コンストラクタ
Stage::Stage() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Stage::~Stage()
{}

//初期化処理
void Stage::Initialize()
{
	//画像の読み込み
	//animation[0] = loadgraph("resource/images/tri-pilot1.png");
	//animation[1] = loadgraph("resource/images/tri-pilot2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 500.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Stage::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	//AnimeControl();

}

//描画処理
void Stage::Draw() const
{
	//プレイヤー画像の描画
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Stage::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Stage::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

//位置情報取得処理
Vector2D Stage::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D Stage::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void Stage::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Stage::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += +5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += -5.0f;
	}
	else
	{
		velocity.x += 0.0f;
	}

	//上下移動
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y += +5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += -5.0f;
	}
	else
	{
		velocity.y += 0.0f;
	}

	//壁の処理
	if (location.x < (scale.x / 2))
	{	//左の壁
		velocity.x += 0.0f;
		location.x = scale.x / 2.0f;
	}
	else if (location.x > (1280.0f - scale.x / 2.0f))
	{	//右の壁
		velocity.x = 0.0f;
		location.x = 1280.0f - scale.x / 2.0f;
	}
	if (location.y < (scale.y / 2.0f))
	{	//上の壁
		velocity.y = 0.0f;
		location.y = scale.y / 2.0f;
	}
	else if (location.y > (720.0f - scale.y / 2.0f))
	{	//下の壁
		velocity.y = 0.0f;
		location.y = 720.0f - scale.y / 2.0f;
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
//void Stage::AnimeControl()
//{
//	//フレームカウントを加算する
//	animation_count++;
//
//	//６０フレーム目に到達したら
//	if (animation_count >= 60)
//	{
//		//カウントのリセット
//		animation_count = 0;
//
//		//画像の切り替え
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}

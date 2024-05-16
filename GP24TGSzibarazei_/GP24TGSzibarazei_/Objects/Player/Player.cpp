#include "Player.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 5;
	mp = 20;
	ult_active = true;
	move_image = 0;

	for (int i = 0; i < 8; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Player::~Player()
{}

//初期化処理
void Player::Initialize()
{
	//前方向画像の読み込み
	animation[0] = LoadGraph("Resource/images/Player/samurai/samurai_front_1.png");
	animation[1] = LoadGraph("Resource/images/Player/samurai/samurai_front_2.png");
	//後ろ方向画像の読み込み
	animation[2] = LoadGraph("Resource/images/Player/samurai/samurai_back_1.png");
	animation[3] = LoadGraph("Resource/images/Player/samurai/samurai_back_2.png");
	//左方向画像の読み込み
	animation[4] = LoadGraph("Resource/images/Player/samurai/samurai_left_1.png");
	animation[5] = LoadGraph("Resource/images/Player/samurai/samurai_left_2.png");
	//右方向画像の読み込み
	animation[6] = LoadGraph("Resource/images/Player/samurai/samurai_right_1.png");
	animation[7] = LoadGraph("Resource/images/Player/samurai/samurai_right_2.png");
	

	//エラーチェック
	for (int i = 0; i < 8; i++)
	{
		if (animation[i] == -1)
		{
			throw("ナイトの画像がありません\n");
		}
	}
	/*if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ナイトの画像がありません\n");
	}*/

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 50.0f;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.02, radian, image, TRUE, flip_flag);
	DrawFormatString(10, 10, GetColor(0, 255, 0), "hp");
	DrawFormatString(10, 25, GetColor(0, 0, 255), "mp");

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
void Player::Finalize()
{
	//使用した画像を開放する
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object,int i)
{
	//当たった時の処理

}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D Player::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void Player::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Player::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		//velocity.x += -5.0f;
		/*flip_flag = TRUE;*/

		//プレイヤー画像を左向きにする
		move_image = 2;
		image = animation[4];
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		//velocity.x += 5.0f;
		/*flip_flag = FALSE;*/

		//プレイヤー画像を右向きにする
		move_image = 3;
		image = animation[6];
	}
	else
	{
		velocity.x += 0.0f;
	}

	//上下移動
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		//velocity.y += -5.0f;

		//プレイヤー画像を後ろ向きにする
		move_image = 1;
		image = animation[2];
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		//velocity.y += 5.0f;

		//プレイヤー画像を前向きにする
		move_image = 0;
		image = animation[0];
	}
	else
	{
		velocity.y += 0.0f;
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

void Player::Atack()
{
	if (InputControl::GetKeyDown(KEY_INPUT_A))
	{
		
	}
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		switch (move_image)
		{
		case 0:
			//画像の切り替え
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
			break;
			
		case 1:
			//画像の切り替え
			if (image == animation[2])
			{
				image = animation[3];
			}
			else
			{
				image = animation[2];
			}
			break;
			
		case 2:
			//画像の切り替え
			if (image == animation[4])
			{
				image = animation[5];
			}
			else
			{
				image = animation[4];
			}
			break;
			
		case 3:
			//画像の切り替え
			if (image == animation[6])
			{
				image = animation[7];
			}
			else
			{
				image = animation[6];
			}
			break;

		}
	}
}

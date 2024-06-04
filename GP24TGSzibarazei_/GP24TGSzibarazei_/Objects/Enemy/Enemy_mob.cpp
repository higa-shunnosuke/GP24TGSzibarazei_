#include "Enemy_mob.h"
#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"
#include<math.h>

Enemy_mob::Enemy_mob() :animation_count(0), ATK(0), Speed(0), AS(0.0), HP(10), AL(3), ET(0), isBoss(false)
{
	for (int i = 0; i < 20; i++) {
		animation[i] = NULL;
	}
}

Enemy_mob::~Enemy_mob()
{
}

void Enemy_mob::Initialize(int enemy_type)
{
	LoadDivGraph("Resource/images/Enemy/troll/troll_all.png", 20, 5, 4, 198, 132, animation);

	//エラーチェック
	for (int i = 0; i < 20; i++)
	{
		if (animation[i] == -1)
		{
			throw("エネミー画像に不備があります\n");
		}
	}

	//向き・大きさ・初期画像の設定
	radian = 0.0f;
	scale = 80.0f;
	image = animation[0];
}

void Enemy_mob::Update()
{

	AnimeControl();

	Movement();

}

void Enemy_mob::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1, radian, image, TRUE, FALSE);

	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = (location - 20.0f) - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy_mob::OnHitCollision(GameObject* hit_object)
{
	//プレイヤー側からダメージの値を貰って、その値分HPを引く
	HP--;
	//HPが0より小さくなったら死亡する※経験値を落とす
	if (HP <= 0)
	{
		//Finalize();
	}
}


void Enemy_mob::SetLocation(const Vector2D& location)
{
}

void Enemy_mob::Movement()
{
	location -= Player::GetVelocity();

	Vector2D PlayerLocation;
	Vector2D PlayeToEnemy;
	//プレイヤーの位置を獲得
	PlayerLocation = Vector2D(600.0f, 360.0f);
	//その方向に向かう
	PlayeToEnemy = PlayerLocation - GetLocation();

	//自身の攻撃範囲を目指してプレイヤーに対して歩く
	if (PlayeToEnemy.y > 0)
	{
		//↓に向かう
		location.y++;
	}
	else if (PlayeToEnemy.y < 0)
	{
		//↑に向かう
		location.y--;
	}

	if (PlayeToEnemy.x > 0)
	{
		if ((image != animation[14]) && (image != animation[15]))
		{
			image = animation[10];
		}

		//右に向かう
		location.x++;
	}
	else if (PlayeToEnemy.x < 0)
	{
		image = animation[0];

		//左に向かう
		location.x--;
	}
}

void Enemy_mob::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		int i = 0, j = 0;
		while (i == 1 || j < 20)
		{
			if (image == animation[j])
			{
				i = 1;
				break;
			}
			j++;
		}
		if (j == 20 && i == 0)
		{
			throw("エネミー画像に不備があります\n");
		}

		//カウントのリセット
		animation_count = 0;


		//5/13

		//画像の切り替え
		if (j == 0)
		{
			image = animation[1];
		}
		if (j == 1)
		{
			image = animation[2];
		}
		if (j == 2)
		{
			image = animation[0];
		}

		if (j == 3)
		{
			image = animation[4];
		}
		if (j == 4)
		{
			image = animation[3];
		}

		if (j == 10)
		{
			image = animation[11];
		}
		if (j == 11)
		{
			image = animation[12];
		}
		if (j == 12)
		{
			image = animation[10];
		}
		/*	if (j == 10)
			{
				image = animation[11];
				ac = 0;
			}
			if (j == 11 && ac == 0)
			{
				image = animation[12];
			}
			if (j == 11 && ac == 1)
			{
				image = animation[10];
			}
			if (j == 12)
			{
				image = animation[11];
				ac = 1;
			}*/

		if (j == 13)
		{
			image = animation[14];
		}
		if (j == 14)
		{
			image = animation[13];
		}


	}
}

Vector2D Enemy_mob::GetLocation() const
{
	return location;
}

Vector2D Enemy_mob::Getscale() const
{
	return scale;
}

void Enemy_mob::Finalize()
{
	//effect付ける
	//徐々に消える
	//使用した画像を開放する
	for (int i = 0; i < 20; i++)
	{
		DeleteGraph(animation[i]);
	}
	//撃破数か何かしらをリターン
}
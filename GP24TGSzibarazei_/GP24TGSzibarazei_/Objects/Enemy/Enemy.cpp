#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"
#include<math.h>

#define M_PI

//typedef struct {
//int Troll_left1 = 0;
//int Troll_left2 = 1;
//int Troll_left3 = 2;
//int Troll_leftwalk1 = 3;
//int Troll_leftwalk2 = 4;
//int Troll_leftatk1 = 5;
//int Troll_leftatk2 = 6;
//int Troll_leftatk3 = 7;
//int Troll_Empty1 = 8;
//int Troll_Empty2 = 9;
//int Troll_right1 = 10;
//int Troll_right2 = 11;
//int Troll_right3 = 12;
//int Troll_rightWalk1 = 13;
//int Troll_rightWalk2 = 14;
//int Troll_rightatk1 = 15;
//int Troll_rightatk2 = 16;
//}Muki;
//
//Muki muki;



Enemy::Enemy() :animation_count(0),ATK (0),Speed(0),AS(0.0),HP(10),AL(3),ET(0),isBoss(false)
{
	for (int i = 0; i < 20; i++) {
		animation[i]  = NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Attack()
{

}

void Enemy::Initialize()
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

void Enemy::Update()
{
	AnimeControl();
	
	Movement();
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1, radian, image, TRUE, FALSE);

	//当たり判定の描画
	__super::Draw();

}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	//プレイヤー側からダメージの値を貰って、その値分HPを引く
	HP--;
	//HPが0より小さくなったら死亡する※経験値を落とす
	if (HP <= 0)
	{
		//Finalize();
	}
}


void Enemy::SetLocation(const Vector2D& location)
{
}

void Enemy::Movement()
{
	//プレイヤーとエネミーの自身の差
	Vector2D diff = player->GetLocation() - this->GetLocation();

	//ベクトルから角度を知る
	float radian = atan2(diff.y, diff.x);

	//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
	location += Vector2D(cosf(radian), sinf(radian));

	if (diff.x>0)
	{
		//左向きの画像
		image = animation[0];
	}
	else if (diff.x < 0)
	{
		//右向きの画像
		image = animation[10];
	}
}

void Enemy::AnimeControl()
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
		if (j == 11 )
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

Vector2D Enemy::GetLocation() const
{
	return location;
}

Vector2D Enemy::Getscale() const
{
	return scale;
}

void Enemy::Finalize()
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

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}
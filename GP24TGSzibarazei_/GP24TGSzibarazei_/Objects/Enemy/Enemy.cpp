#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"
#include<math.h>
#include"../../Scenes/SceneBase.h"
#include"Enemy_Attack.h"

Enemy_Attack* EA;
static int type;

Enemy::Enemy() :animation_count(0),ATK (10),Speed(1),AS(15.0),HP(10),AL(80),ET(0),isBoss(false)
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
	if (EA->SetEnemy(ATK, AL, AS,this->location) == false)
	{
		throw("エネミーとエネミーアタック間の値渡しに問題があります。");
	}
	CreateObject<Enemy_Attack>(this->location,0);

}

void Enemy::Initialize(int enemy_type)
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

	EA = CreateObject<Enemy_Attack>(Vector2D(),0);
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
	if (hit_object == player)
	{
	//プレイヤー側からダメージの値を貰って、その値分HPを引く
	HP--;
	}

	//HPが0より小さくなったら死亡する※経験値を落とす
	if (HP <= 0)
	{
		DeleteObject(this);
	}
}


void Enemy::SetLocation(const Vector2D& location)
{
}

void Enemy::Movement()
{

	location -= player->GetVelocity();
	//プレイヤーとエネミーの自身の差
	Vector2D diff = player->GetLocation() - this->GetLocation();

	//ベクトルから角度を知る
	float radian = (float)atan2(diff.y, diff.x);

	if (diff.x > AL)
	{
		if (image != animation[13] && image != animation[14])
		{
			//右向きの画像
			image = animation[13];
		}
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.x < -AL)
	{
		if (image != animation[3] && image != animation[4])
		{
			//左向きの画像
			image = animation[3];
		}
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y > AL)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y < -AL)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (image == animation[13] || image == animation[14])
	{
		image = animation[10];
		Attack();
	}
	else if (image == animation[3] || image == animation[4])
	{
		image = animation[0];
		Attack();
	}
}

void Enemy::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	//現在のアニメーション画像が今どの段階かを取得する(jがAnimの現在を所持する)(iは終了時処理を行うため特に不要)
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

//ステージのタイプ取得処理
int Enemy::GetType() const
{
	return type;
}
#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"

Enemy::Enemy() :animation_count(0),ATK (0),Speed(0),AS(0.0),HP(10),AL(15)
{
	int i;
	for (i = 0; i < 15; i++) {
		animation[i]  = NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//後々イラストをもらい次第実装確認
	//左向き
	animation[0] = LoadGraph("Resource/images/Enemy/troll/troll_left_1.png");
	animation[1] = LoadGraph("Resource/images/Enemy/troll/troll_left_2.png");
	animation[2] = LoadGraph("Resource/images/Enemy/troll/troll_left_3.png");

	//左歩き
	animation[3] = LoadGraph("Resource/images/Enemy/troll/troll_left_walk_1.png");
	animation[4] = LoadGraph("Resource/images/Enemy/troll/troll_left_walk_2.png");
	//左攻撃
	animation[5] = LoadGraph("Resource/images/Enemy/troll/troll_left_atk_1.png");
	animation[6] = LoadGraph("Resource/images/Enemy/troll/troll_left_atk_2.png");
	animation[7] = LoadGraph("Resource/images/Enemy/troll/troll_left_atk_3.png");

	//右向き
	animation[8] = LoadGraph("Resource/images/Enemy/troll/troll_right_1.png");
	animation[9] = LoadGraph("Resource/images/Enemy/troll/troll_right_2.png");
	animation[10] = LoadGraph("Resource/images/Enemy/troll/troll_right_3.png");
	//右歩き
	animation[11] = LoadGraph("Resource/images/Enemy/troll/troll_right_walk_1.png");
	animation[12] = LoadGraph("Resource/images/Enemy/troll/troll_right_walk_2.png");
	//右攻撃
	animation[13] = LoadGraph("Resource/images/Enemy/troll/troll_right_fist_atk_1.png");
	animation[14] = LoadGraph("Resource/images/Enemy/troll/troll_right_fist_atk_2.png");

	int i = 0;




	//0=69730313 1=69992458 2=70254603  3=70516748  4=70778893  5=71041038  6=71041038 
	//7=71565328 8=71827473 9=72089618 10=72351763 11=72613908 12=72876053 13=73138198 14=73400343


	//エラーチェック
	for (int i = 0; i < 15; i++)
	{
		if (animation[i] == -1)
		{
			throw("エネミー画像に不備があります\n");
		}
	}

	//向き・大きさ・初期画像の設定
	radian = 0.0f;
	scale = 50.0f;
	image = animation[0];
}

void Enemy::Update()
{

	AnimeControl();
	
	Movement();

}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.02, radian, image, TRUE, FALSE);

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


	Vector2D PlayerLocation;
	Vector2D PlayeToEnemy;
	//プレイヤーの位置を獲得
	PlayerLocation = (640.0f, 360.0f);
	//その方向に向かう
	PlayeToEnemy = PlayerLocation - GetLocation();

	//自身の攻撃範囲を目指してプレイヤーに対して歩く
	if (PlayeToEnemy.y > 0 + AL)
	{
		//上に向かう
		location.y++;
	}
	else if (PlayeToEnemy.y < 0 + AL)
	{
		//下に向かう
		location.y--;
	}

	if (PlayeToEnemy.x > 0 + AL)
	{
		if ((image != animation[9]) && (image != animation[10]))
		{
		image = animation[8];
		}

		//右に向かう
		location.x++;
	}
	else if (PlayeToEnemy.x < 0 + AL)
	{
		//左に向かう
		location.x--;
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
		while (i == 1 || j < 15)
		{
			if (image == animation[j])
			{
				i = 1;
				break;
			}
			j++;
		}
		if (j == 15 && i == 0)
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

		if (j == 8)
		{
			image = animation[9];
		}
		if (j == 9)
		{
			image = animation[10];
		}
		if (j == 10)
		{
			image = animation[8];
		}

		if (j == 11)
		{
			image = animation[12];
		}
		if (j == 12)
		{
			image = animation[11];
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
	for (int i = 0; i < 15; i++)
	{
		DeleteGraph(animation[i]);
	}
	//撃破数か何かしらをリターン
}
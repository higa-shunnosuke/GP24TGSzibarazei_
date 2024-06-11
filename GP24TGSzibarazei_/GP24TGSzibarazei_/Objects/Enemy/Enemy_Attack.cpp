#include "Enemy_Attack.h"
#include"DxLib.h"

Enemy_Attack::Enemy_Attack():AL(-1),ATK(-1),AS(-1.0f),scale(1.0f),animation_count(0)
{
	for (int i = 0; i < 25; i++)
	{
		animation[i] = NULL;
	}

	animation[0] = LoadGraph("Resource/images/troll/Attack/1.png");
	animation[1] = LoadGraph("Resource/images/troll/Attack/2.png");
	animation[2] = LoadGraph("Resource/images/troll/Attack/3.png");
	animation[3] = LoadGraph("Resource/images/troll/Attack/4.png");
	animation[4] = LoadGraph("Resource/images/troll/Attack/5.png");
	animation[5] = LoadGraph("Resource/images/troll/Attack/6.png");
	animation[6] = LoadGraph("Resource/images/troll/Attack/7.png");
	animation[7] = LoadGraph("Resource/images/troll/Attack/8.png");
	animation[8] = LoadGraph("Resource/images/troll/Attack/9.png");
	animation[9] = LoadGraph("Resource/images/troll/Attack/10.png");
	animation[10] = LoadGraph("Resource/images/troll/Attack/11.png");
	animation[11] = LoadGraph("Resource/images/troll/Attack/12.png");
	animation[12] = LoadGraph("Resource/images/troll/Attack/13.png");
	animation[13] = LoadGraph("Resource/images/troll/Attack/14.png");
	animation[14] = LoadGraph("Resource/images/troll/Attack/15.png");
	animation[15] = LoadGraph("Resource/images/troll/Attack/16.png");
	animation[16] = LoadGraph("Resource/images/troll/Attack/17.png");
	animation[17] = LoadGraph("Resource/images/troll/Attack/18.png");
	animation[18] = LoadGraph("Resource/images/troll/Attack/19.png");
	animation[19] = LoadGraph("Resource/images/troll/Attack/20.png");
	animation[20] = LoadGraph("Resource/images/troll/Attack/21.png");
	animation[21] = LoadGraph("Resource/images/troll/Attack/22.png");
	animation[22] = LoadGraph("Resource/images/troll/Attack/23.png");
	animation[23] = LoadGraph("Resource/images/troll/Attack/24.png");
	animation[24] = LoadGraph("Resource/images/troll/Attack/25.png");

	anim = animation[0];
}

Enemy_Attack::~Enemy_Attack()
{
}

bool Enemy_Attack::SetEnemy(int ATK, int AL, float AS ,Vector2D loc)
{
	if (ATK == -1 || AL == -1 || AS == -1.0f){
		return false;
	}
	this->ATK = ATK;
	this->AL = AL;
	this->AS = AS;
	this->location = loc;

	return true;
}

void Enemy_Attack::OnHitCollision(GameObject* hit_object)
{
}

Vector2D Enemy_Attack::GetLocation() const
{
	return Vector2D();
}

Vector2D Enemy_Attack::Getscale() const
{
	return Vector2D();
}

void Enemy_Attack::SetLocation(const Vector2D& location)
{
}

void Enemy_Attack::Initialize()
{
}

void Enemy_Attack::Attack()
{
}

void Enemy_Attack::Update()
{
	Draw();

	Movement();
}

void Enemy_Attack::Draw() const
{
	DrawGraph(location.x, location.y, anim, false);
	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (scale / 2.0f);
	Vector2D box_collision_upper_right = location + (scale / 2.0f) + (float)AL;

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy_Attack::Finalize()
{
	for (int i = 0; i < 25; i++)
	{
		DeleteGraph(animation[i]);
	}
}

void Enemy_Attack::Movement()
{
	animation_count++;
	int i = 0; int j = 0;
	//引用文※Enemyを参照
	if (animation_count <= 20)
	{
		while (i == 1 || j < 25)
		{
			if (image == animation[j])
			{
				i = 1;
				break;
			}
			j++;
		}
		if (j <= 24)
		{
			//24終端だから０に戻す
			j = 0;
		}
		else {
			//jを加算する(次の画像を描画したいから)
			j++;
		}

		//本文(描画する画像の変数に次の画像をセットする)
		anim = animation[j];

	}
}

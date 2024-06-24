#include "Enemy_Attack.h"
#include"DxLib.h"


static int type;

Enemy_Attack::Enemy_Attack():AL(-1),ATK(-1),AS(-1.0f),isHit(false)
{
	LoadDivGraph("Resource/images/Enemy/troll/Attack/enemy_atk_all.png", 20, 5, 5, 180, 180, animation);
	anim = animation[0];
	scale = 100.0f;
}

Enemy_Attack::~Enemy_Attack()
{
}

bool Enemy_Attack::SetEnemy(int ATK, int AL, float AS ,Vector2D loc,Player* p,Enemy* e)
{
	if (ATK == -1 || AL == -1 || AS == -1.0f){
		return false;
	}
	this->ATK = ATK;
	this->AL = AL;
	this->AS = AS;
	this->location = loc;
	this->player = p;
	this->enemy = e;

	return true;
}

void Enemy_Attack::OnHitCollision(GameObject* hit_object)
{
	if (hit_object == player&& isHit != true)
	{
		player->HitAttack(1);
		isHit = true;
	}


}

Vector2D Enemy_Attack::GetLocation() const
{
	return location;
}

Vector2D Enemy_Attack::Getscale() const
{
	return scale;
}

void Enemy_Attack::Initialize(int enemy_type)
{
}

void Enemy_Attack::Attack()
{
}

void Enemy_Attack::Update()
{

	location -= player->GetVelocity();

	Movement();

	AnimControl();

}

void Enemy_Attack::Draw() const
{

	// 動画を指定した位置とサイズで描画
	DrawRotaGraphF(location.x,location.y,1,radian, anim, 1,1,0);

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

void Enemy_Attack::Finalize()
{
	if (enemy != nullptr && anim == animation[19])
	{
		enemy->AttackMore(true);
		enemy = nullptr;
	}
}

void Enemy_Attack::Movement()
{

	//プレイヤーとエネミーの自身の差
	Vector2D diff = player->GetLocation() - this->GetLocation();


	//ベクトルから角度を知る
	float radian = (float)atan2(diff.y, diff.x);

	if (diff.x > 0)
	{
		
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.x < 0)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y > 0)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y < 0)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian));
	}

}

void Enemy_Attack::AnimControl()
{
	animation_count++;
	if (animation_count >= 20)
	{
		int i = 0, j = 0;
		while (i == 1 || j < 20)
		{
			if (anim == animation[j])
			{
				i = 1;
				break;
			}
			j++;
		}
		if (j == 19)
		{
			Deleteclass(this);
		}else{
				j++;
		}
		
		anim = animation[j];
	}
}
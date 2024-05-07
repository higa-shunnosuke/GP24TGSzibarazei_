#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :animation_count(0),ATK (0),Speed(0),AS(0.0),HP(0)
{
	int i;
	for (i = 0; i < 8; i++) {
		animation[i]=NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//後々イラストをもらい次第実装確認
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	
	//エラーチェック
	for (int i = 0; i < 8; i++)
	{
		if (animation[i] == -1)
		{
			throw("エネミー画像に不備があります\n");
		}
	}

	//向き・大きさ・初期画像の設定
	radian = 0.0f;
	scale = 5.0f;
	image = animation[0];
}

void Enemy::Update()
{



}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.4, radian, image, TRUE, TRUE);


}

void Enemy::Finalize()
{
	//使用した画像を開放する
	for (int i = 0; i < 8; i++)
	{
	DeleteGraph(animation[i]);
	}
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
}


void Enemy::SetLocation(const Vector2D& location)
{
}

void Enemy::Movement()
{
	
}

void Enemy::AnimeControl()
{
}

Vector2D Enemy::GetLocation() const
{
	return location;
}

Vector2D Enemy::Getscale() const
{
	return scale;
}
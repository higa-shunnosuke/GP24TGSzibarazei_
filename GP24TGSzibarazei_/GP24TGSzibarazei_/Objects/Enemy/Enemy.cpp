#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy() :animation_count(0)
{
	int i;
	for (i = 0; i < 4; i++) {
		animation[i]=NULL;
	}
}

Enemy::~Enemy()
{}

void Enemy::Initialize()
{
	animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	
	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("エネミー画像[%2d]に不備があります\n", i);
		}
	}

	//向き・大きさ・初期画像の設定
	radian = 0.0f;
	scale = 5.0f;
	image = animation[0];
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.4, radian, image, TRUE, TRUE);


}
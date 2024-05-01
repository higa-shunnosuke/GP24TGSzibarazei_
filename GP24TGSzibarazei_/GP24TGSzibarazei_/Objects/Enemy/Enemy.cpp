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
	
	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�G�l�~�[�摜�ɕs��������܂�\n");
		}
	}

	//�����E�傫���E�����摜�̐ݒ�
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
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
}

Vector2D Enemy::GetLocation() const
{
	return Vector2D();
}

Vector2D Enemy::Getscale() const
{
	return Vector2D();
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

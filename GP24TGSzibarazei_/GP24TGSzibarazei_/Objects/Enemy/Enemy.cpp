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
	//��X�C���X�g�����炢��������m�F
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	
	//�G���[�`�F�b�N
	for (int i = 0; i < 8; i++)
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
	//�g�p�����摜���J������
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
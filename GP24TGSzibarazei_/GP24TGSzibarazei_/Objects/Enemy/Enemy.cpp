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
			throw("�G�l�~�[�摜[%2d]�ɕs��������܂�\n", i);
		}
	}

	//�����E�傫���E�����摜�̐ݒ�
	radian = 0.0f;
	scale = 5.0f;
	image = animation[0];
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.4, radian, image, TRUE, TRUE);


}
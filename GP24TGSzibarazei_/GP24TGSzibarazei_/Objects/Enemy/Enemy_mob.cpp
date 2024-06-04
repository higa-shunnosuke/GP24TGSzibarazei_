#include "Enemy_mob.h"
#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"
#include<math.h>

Enemy_mob::Enemy_mob() :animation_count(0), ATK(0), Speed(0), AS(0.0), HP(10), AL(3), ET(0), isBoss(false)
{
	for (int i = 0; i < 20; i++) {
		animation[i] = NULL;
	}
}

Enemy_mob::~Enemy_mob()
{
}

void Enemy_mob::Initialize(int enemy_type)
{
	LoadDivGraph("Resource/images/Enemy/troll/troll_all.png", 20, 5, 4, 198, 132, animation);

	//�G���[�`�F�b�N
	for (int i = 0; i < 20; i++)
	{
		if (animation[i] == -1)
		{
			throw("�G�l�~�[�摜�ɕs��������܂�\n");
		}
	}

	//�����E�傫���E�����摜�̐ݒ�
	radian = 0.0f;
	scale = 80.0f;
	image = animation[0];
}

void Enemy_mob::Update()
{

	AnimeControl();

	Movement();

}

void Enemy_mob::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1, radian, image, TRUE, FALSE);

	//�f�o�b�N�p
#if _DEBUG
//�����蔻��̉���
	Vector2D box_collision_upper_left = (location - 20.0f) - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy_mob::OnHitCollision(GameObject* hit_object)
{
	//�v���C���[������_���[�W�̒l�����āA���̒l��HP������
	HP--;
	//HP��0��菬�����Ȃ����玀�S���遦�o���l�𗎂Ƃ�
	if (HP <= 0)
	{
		//Finalize();
	}
}


void Enemy_mob::SetLocation(const Vector2D& location)
{
}

void Enemy_mob::Movement()
{
	location -= Player::GetVelocity();

	Vector2D PlayerLocation;
	Vector2D PlayeToEnemy;
	//�v���C���[�̈ʒu���l��
	PlayerLocation = Vector2D(600.0f, 360.0f);
	//���̕����Ɍ�����
	PlayeToEnemy = PlayerLocation - GetLocation();

	//���g�̍U���͈͂�ڎw���ăv���C���[�ɑ΂��ĕ���
	if (PlayeToEnemy.y > 0)
	{
		//���Ɍ�����
		location.y++;
	}
	else if (PlayeToEnemy.y < 0)
	{
		//���Ɍ�����
		location.y--;
	}

	if (PlayeToEnemy.x > 0)
	{
		if ((image != animation[14]) && (image != animation[15]))
		{
			image = animation[10];
		}

		//�E�Ɍ�����
		location.x++;
	}
	else if (PlayeToEnemy.x < 0)
	{
		image = animation[0];

		//���Ɍ�����
		location.x--;
	}
}

void Enemy_mob::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
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
			throw("�G�l�~�[�摜�ɕs��������܂�\n");
		}

		//�J�E���g�̃��Z�b�g
		animation_count = 0;


		//5/13

		//�摜�̐؂�ւ�
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
		if (j == 11)
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

Vector2D Enemy_mob::GetLocation() const
{
	return location;
}

Vector2D Enemy_mob::Getscale() const
{
	return scale;
}

void Enemy_mob::Finalize()
{
	//effect�t����
	//���X�ɏ�����
	//�g�p�����摜���J������
	for (int i = 0; i < 20; i++)
	{
		DeleteGraph(animation[i]);
	}
	//���j����������������^�[��
}
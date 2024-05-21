#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"

Enemy::Enemy() :animation_count(0),ATK (0),Speed(0),AS(0.0),HP(10),AL(15),ac(0)
{
	int i;
	for (i = 0; i < 20; i++) {
		animation[i]  = NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//��X�C���X�g�����炢��������m�F
	//������
	LoadDivGraph("Resource/images/Enemy/troll/troll_all.png", 20, 5, 4, 198, 132, animation);

	int i = 0;



	//0=69730313 1=69992458 2=70254603  3=70516748  4=70778893  5=71041038  6=71041038 
	//7=71565328 8=71827473 9=72089618 10=72351763 11=72613908 12=72876053 13=73138198 14=73400343


	//�G���[�`�F�b�N
	for (int i = 0; i < 15; i++)
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

void Enemy::Update()
{

	AnimeControl();
	
	Movement();

}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1, radian, image, TRUE, FALSE);

	//�f�o�b�N�p
#if _DEBUG
//�����蔻��̉���
	Vector2D box_collision_upper_left =  (location - 60.0f) - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	box_collision_upper_left.y += 73.0f;
	Vector2D box_collision_upper_right = (location - 50.0f) + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);
	box_collision_upper_right.y += 73.0f;

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy::OnHitCollision(GameObject* hit_object,int i)
{
	//�v���C���[������_���[�W�̒l�����āA���̒l��HP������
	HP--;
	//HP��0��菬�����Ȃ����玀�S���遦�o���l�𗎂Ƃ�
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
	//�v���C���[�̈ʒu���l��
	PlayerLocation = (640.0f, 360.0f);
	//���̕����Ɍ�����
	PlayeToEnemy = PlayerLocation - GetLocation();

	//���g�̍U���͈͂�ڎw���ăv���C���[�ɑ΂��ĕ���
	if (PlayeToEnemy.y > 0 + AL)
	{
		//��Ɍ�����
		location.y++;
	}
	else if (PlayeToEnemy.y < 0 + AL)
	{
		//���Ɍ�����
		location.y--;
	}

	if (PlayeToEnemy.x > 0 + AL)
	{
		if ((image != animation[14]) && (image != animation[15]))
		{
		image = animation[10];
		}

		//�E�Ɍ�����
		location.x++;
	}
	else if (PlayeToEnemy.x < 0 + AL)
	{
		//���Ɍ�����
		location.x--;
	}
}

void Enemy::AnimeControl()
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
			ac = 0;
		}
		if (j == 1 && ac == 0)
		{
			image = animation[2];
		}
		if (j == 1 && ac == 1)
		{
			image = animation[0];
		}
		if (j == 2)
		{
			image = animation[1];
			ac = 1;
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
		}

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
	//effect�t����
	//���X�ɏ�����
	//�g�p�����摜���J������
	for (int i = 0; i < 20; i++)
	{
		DeleteGraph(animation[i]);
	}
	//���j����������������^�[��
}
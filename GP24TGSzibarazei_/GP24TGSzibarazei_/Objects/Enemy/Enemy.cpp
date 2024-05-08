#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"

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

	//�f�o�b�N�p
#if _DEBUG
//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
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
	HP--;
	if (HP == 0)
	{
		Finalize();
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
	if (PlayeToEnemy.y > 0)
	{
		//��Ɍ�����
		location.y++;
		WaitTimer(60);
	}
	else if (PlayeToEnemy.y < 0)
	{
		//���Ɍ�����
		location.y--;
		WaitTimer(60);

	}

	if (PlayeToEnemy.x > 0)
	{
		//���Ɍ�����
		location.x++;
		WaitTimer(60);

	}
	else if (PlayeToEnemy.x < 0)
	{
		//�E�Ɍ�����
		location.x--;
		WaitTimer(60);
	}

	//�������Ȃ�A�����
	//���g�̍U���͈͂�ڎw���ăv���C���[�ɑ΂��ĕ���
	if (PlayeToEnemy.y > 0)
	{
		location.y--;
		WaitTimer(60);
	}
	else if (PlayeToEnemy.y < 0)
	{
		location.y++;
		WaitTimer(60);

	}

	if (PlayeToEnemy.x > 0)
	{
		location.x--;
		WaitTimer(60);

	}
	else if (PlayeToEnemy.x < 0)
	{
		location.x++;
		WaitTimer(60);
	}
	//�X�e�[�W�̈ړ��ɍ��킹�ē���
}

void Enemy::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
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
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
	//���j����������������^�[��
}
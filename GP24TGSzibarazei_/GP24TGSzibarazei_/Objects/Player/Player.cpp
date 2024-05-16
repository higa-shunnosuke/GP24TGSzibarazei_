#include "Player.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 5;
	mp = 20;
	ult_active = true;
	move_image = 0;

	for (int i = 0; i < 8; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Player::~Player()
{}

//����������
void Player::Initialize()
{
	//�O�����摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/images/Player/samurai/samurai_front_1.png");
	animation[1] = LoadGraph("Resource/images/Player/samurai/samurai_front_2.png");
	//�������摜�̓ǂݍ���
	animation[2] = LoadGraph("Resource/images/Player/samurai/samurai_back_1.png");
	animation[3] = LoadGraph("Resource/images/Player/samurai/samurai_back_2.png");
	//�������摜�̓ǂݍ���
	animation[4] = LoadGraph("Resource/images/Player/samurai/samurai_left_1.png");
	animation[5] = LoadGraph("Resource/images/Player/samurai/samurai_left_2.png");
	//�E�����摜�̓ǂݍ���
	animation[6] = LoadGraph("Resource/images/Player/samurai/samurai_right_1.png");
	animation[7] = LoadGraph("Resource/images/Player/samurai/samurai_right_2.png");
	

	//�G���[�`�F�b�N
	for (int i = 0; i < 8; i++)
	{
		if (animation[i] == -1)
		{
			throw("�i�C�g�̉摜������܂���\n");
		}
	}
	/*if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�i�C�g�̉摜������܂���\n");
	}*/

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 50.0f;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Player::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.02, radian, image, TRUE, flip_flag);
	DrawFormatString(10, 10, GetColor(0, 255, 0), "hp");
	DrawFormatString(10, 25, GetColor(0, 0, 255), "mp");

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

//�I��������
void Player::Finalize()
{
	//�g�p�����摜���J������
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object,int i)
{
	//�����������̏���

}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�傫���擾����
Vector2D Player::Getscale() const
{
	return this->scale;
}

//�ʒu���ݒ菈��
void Player::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�ړ�����
void Player::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		//velocity.x += -5.0f;
		/*flip_flag = TRUE;*/

		//�v���C���[�摜���������ɂ���
		move_image = 2;
		image = animation[4];
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		//velocity.x += 5.0f;
		/*flip_flag = FALSE;*/

		//�v���C���[�摜���E�����ɂ���
		move_image = 3;
		image = animation[6];
	}
	else
	{
		velocity.x += 0.0f;
	}

	//�㉺�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		//velocity.y += -5.0f;

		//�v���C���[�摜���������ɂ���
		move_image = 1;
		image = animation[2];
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		//velocity.y += 5.0f;

		//�v���C���[�摜��O�����ɂ���
		move_image = 0;
		image = animation[0];
	}
	else
	{
		velocity.y += 0.0f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

void Player::Atack()
{
	if (InputControl::GetKeyDown(KEY_INPUT_A))
	{
		
	}
}

//�A�j���[�V��������
void Player::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		switch (move_image)
		{
		case 0:
			//�摜�̐؂�ւ�
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
			break;
			
		case 1:
			//�摜�̐؂�ւ�
			if (image == animation[2])
			{
				image = animation[3];
			}
			else
			{
				image = animation[2];
			}
			break;
			
		case 2:
			//�摜�̐؂�ւ�
			if (image == animation[4])
			{
				image = animation[5];
			}
			else
			{
				image = animation[4];
			}
			break;
			
		case 3:
			//�摜�̐؂�ւ�
			if (image == animation[6])
			{
				image = animation[7];
			}
			else
			{
				image = animation[6];
			}
			break;

		}
	}
}

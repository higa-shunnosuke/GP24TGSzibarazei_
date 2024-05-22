#include "Player.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"


static Vector2D velocity;		//�ړ�����

//�R���X�g���N�^
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 4;
	max_hp = 5;
	mp = 20;
	level = 1;
	exp = 0;
	max_exp = 4;
	ult_count = 0;
	ult_active = false;
	move_image = 0;
	move_flag = 1;

	//�ړ�����
	velocity = Vector2D(0.0f);

	for (int i = 0; i < 8; i++)
	{
		animation[i] = NULL;
	}
	for (int i = 0; i < 7; i++)
	{
		ui_image[i] = NULL;
	}
}

//�f�X�g���N�^
Player::~Player()
{}

//����������
void Player::Initialize()
{
	//�O�����摜�̓ǂݍ���
	LoadDivGraph("Resource/images/Player/samurai/samurai_all.png", 30, 6, 6, 133, 166, animation);

	///////////////////////�摜�ǉ��\��
	////HP�摜
	ui_image[0] = LoadGraph("Resource/images/Player/ui/Hp1.png");
	ui_image[1] = LoadGraph("Resource/images/Player/ui/Hp2.png");
	
	////MP�摜
	//ui_image[3] = LoadGraph("Resource/images/Player/ui/Mp_1.png");
	//ui_image[4] = LoadGraph("Resource/images/Player/ui/Mp_2.png");
	//ui_image[5] = LoadGraph("Resource/images/Player/ui/Mp_3.png");
	////Level�摜
	//ui_image[6] = LoadGraph("Resource/images/Player/ui/Exp_1.png");
	

	////�G���[�`�F�b�N�i�L�����摜�j
	//for (int i = 0; i < 36; i++)
	//{
	//	if (animation[i] == -1)
	//	{
	//		throw("�i�C�g�̉摜������܂���\n");
	//	}
	//}
	if (animation[0] == -1)
	{
		throw("�i�C�g�̉摜������܂���\n");
	}

	////////////////////�摜�ǉ��\��
	//�G���[�`�F�b�N�iUI�摜�j
	for (int i = 0; i < 2; i++)
	{
		if (ui_image[i] == -1)
		{
			throw("UI�摜������܂���\n");
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

	//�ړ�����
	velocity = Vector2D(0.0f);
}

//�X�V����
void Player::Update()
{
	if (move_flag = 1)
	{
		//�ړ�����
		Movement();
		//�U������
		Atack();
		//�A�j���[�V��������
		AnimeControl();
	}
	else if (move_flag == 0)
	{
		//�p�b�V�u�l������
		AcquisitionPassive();
	}
}

//�`�揈��
void Player::Draw() const
{
	if (move_flag == 1)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
		//HP�摜�̕`��
		for (int i = 0; i < max_hp; i++)
		{
			if (i <= hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[0], TRUE, flip_flag);
			}
			else
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[1], TRUE, flip_flag);
			}
		}
	}
	else if (move_flag == 0)
	{
		DrawFormatString(location.x, location.y, GetColor(0, 255, 0), "LevelUp");
	}
	
	DrawFormatString(10, 25, GetColor(0, 0, 255), "mp");
	DrawFormatString(50, 10, GetColor(0, 0, 255), "%d",exp);
	DrawFormatString(50, 25, GetColor(0, 0, 255), "%d", max_exp);
	DrawFormatString(50, 35, GetColor(255, 0, 0), "%d", level);
	DrawFormatString(480, 360, GetColor(255, 0, 0), "%d", ult_count);
	if (ult_active == true)
	{
		DrawFormatString(480, 380, GetColor(255, 0, 0), "ok");
	}
	else if (ult_active == false)
	{
		DrawFormatString(480, 340, GetColor(255, 0, 0), "no");
	}
	//�f�o�b�N�p
	__super::Draw();
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜���J������
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
	//�g�p�����摜���J������
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(ui_image[i]);
	}
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object,int i)
{
	//�����������̏���
	//hp--;
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
	velocity = Vector2D(0.0f);

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += -5.0f;

		//�v���C���[�摜���������ɂ���
		move_image = 2;
		image = animation[4];
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity.x += 5.0f;

		//�v���C���[�摜���E�����ɂ���
		move_image = 3;
		image = animation[6];
	}
	else
	{
		velocity.x += 0.0f;
	}

	//�㉺�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity.y += -5.0f;

		//�v���C���[�摜���������ɂ���
		move_image = 1;
		image = animation[2];
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += 5.0f;

		//�v���C���[�摜��O�����ɂ���
		move_image = 0;
		image = animation[0];
	}
	else
	{
		velocity.y += 0.0f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	//location += velocity;
}

void Player::Atack()
{
	if(ult_count<=1800)
	ult_count++;
	if (ult_count >= 1800)
	{
		ult_active = true;
	}
	if (InputControl::GetKeyDown(KEY_INPUT_Q) && ult_active==true)
	{
		ult_active = false;
		ult_count = 0;
		Ultimate();
	}

	int get = 2;
	if (InputControl::GetKeyDown(KEY_INPUT_A))
	{
		LevelUp(get);
	}
	if (InputControl::GetKeyDown(KEY_INPUT_S))
	{
		hp--;
		if (hp < -1)
		{
			hp = -1;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_D))
	{
		hp++;
		if (hp > max_hp-1)
		{
			hp = max_hp-1;
		}
	}
	Ultimate();
}

void Player::Ultimate()
{
	
}

void Player::LevelUp(int get_exp)
{
	//���݂̌o���l�Ɏ擾�����o���l�����Z
	exp += get_exp;
	//���x���A�b�v�ɕK�v�Ȍo���l�����܂����Ƃ�
	if (exp >= max_exp)
	{
		//���x����1�グ��
		level++;
		//�]�����o���l�����݂̌o���l�ɂ���
		exp = max_exp - exp;
		//���̃��x���A�b�v�ɕK�v�Ȍo���l�𑝂₷
		max_exp=max_exp * 2;
		move_flag = 0;
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


void Player::AcquisitionPassive()
{
	if (InputControl::GetKeyDown(KEY_INPUT_V))
	{
		move_flag = 1;
	}
}

//�ړ������擾����
Vector2D Player::GetVelocity()
{
	return velocity;
}

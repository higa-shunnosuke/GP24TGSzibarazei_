#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../Stage/Stage.h"
#include "DxLib.h"


static Vector2D velocity;		//�ړ�����

//�ǂ����������Ă��邩
static bool hit_l;
static bool hit_r;
static bool hit_u;
static bool hit_d;

//�R���X�g���N�^
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 4;
	max_hp = 5;
	limit_hp = 0;
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
	for (int i = 0; i < 10; i++)
	{
		number_image[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		ui_number[i] = NULL;
	}
}

//�f�X�g���N�^
Player::~Player()
{}

//����������
void Player::Initialize(int player_type)
{
	//�O�����摜�̓ǂݍ���
	LoadDivGraph("Resource/images/Player/knight/knight_all.png", 23, 5, 5, 160, 200, animation);

	///////////////////////�摜�ǉ��\��
	////HP�摜
	ui_image[0] = LoadGraph("Resource/images/Player/ui/Hp1.png");
	ui_image[1] = LoadGraph("Resource/images/Player/ui/Hp2.png");
	ui_image[2] = LoadGraph("Resource/images/Player/ui/HpArmor2.png");
	////�A���e�B���b�g�摜
	ui_image[3] = LoadGraph("Resource/images/Player/ui/ult_put.png");
	ui_image[4] = LoadGraph("Resource/images/Player/ui/ult_icon.png");
	////MP�摜
	//ui_image[3] = LoadGraph("Resource/images/Player/ui/Mp_1.png");
	//ui_image[4] = LoadGraph("Resource/images/Player/ui/Mp_2.png");
	//ui_image[5] = LoadGraph("Resource/images/Player/ui/Mp_3.png");
	////Level�摜
	//ui_image[6] = LoadGraph("Resource/images/Player/ui/Exp_1.png");
	
	////�����摜
	number_image[0] = LoadGraph("Resource/images/Player/ui/number_0.png");
	number_image[1] = LoadGraph("Resource/images/Player/ui/number_1.png");
	number_image[2] = LoadGraph("Resource/images/Player/ui/number_2.png");
	number_image[3] = LoadGraph("Resource/images/Player/ui/number_3.png");
	number_image[4] = LoadGraph("Resource/images/Player/ui/number_4.png");
	number_image[5] = LoadGraph("Resource/images/Player/ui/number_5.png");
	number_image[6] = LoadGraph("Resource/images/Player/ui/number_6.png");
	number_image[7] = LoadGraph("Resource/images/Player/ui/number_7.png");
	number_image[8] = LoadGraph("Resource/images/Player/ui/number_8.png");
	number_image[9] = LoadGraph("Resource/images/Player/ui/number_9.png");

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
	for (int i = 0; i < 4; i++)
	{
		if (ui_image[i] == -1)
		{
			throw("UI�摜������܂���\n");
		}
	}

	/*for (int i = 0; i < 10; i++)
	{
		if (number_image[i] == -1)
		{
			throw("�����摜������܂���\n");
		}
	}*/

	/*if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�i�C�g�̉摜������܂���\n");
	}*/

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 50.0f;

	//�����摜�̐ݒ�
	image = animation[5];

	//�ړ�����
	velocity = Vector2D(0.0f);
}

//�X�V����
void Player::Update()
{
	if (move_flag == 1)
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

	//hit���������i�ړ������̌�ɏ���������j
	hit_l = false;
	hit_r = false;
	hit_u = false;
	hit_d = false;
}

//�`�揈��
void Player::Draw() const
{
	if (move_flag == 1)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
		//HP�摜�̕`��
		for (int i = 0; i < max_hp+limit_hp; i++)
		{
			if (i <= hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[0], TRUE, flip_flag);
			}
			else if(i<max_hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[1], TRUE, flip_flag);
			}
			else
			{
				DrawRotaGraphF(30.0f + (i * 50.f), 25.f, 0.04, radian, ui_image[2], TRUE, flip_flag);
			}
		}
	}
	else if (move_flag == 0)
	{
		DrawFormatString(location.x, location.y, GetColor(0, 255, 0), "LevelUp");
	}
	//�A���e�B���b�g�`��
	DrawRotaGraphF(1050.f, 500.f,1.5, radian, ui_image[3], TRUE, flip_flag);
	DrawRotaGraphF(1050.f, 500.f, 2, radian, ui_image[4], TRUE, flip_flag);

	//���̑�
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
void Player::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//hp--;
	
	Vector2D pl = this->GetLocation();
	Vector2D ps = this->GetBoxSize() / 2.0f;
	Vector2D ol = hit_object->GetLocation();
	Vector2D os = hit_object->GetBoxSize() / 2.0f;

	//������
	//�v���C���[�̍������X�e�[�W�̍������E�̂Ƃ�
	if (pl.x-ps.x >= ol.x-os.x)
	{
		hit_l = true;
	}
	//�v���C���[�̉E�����X�e�[�W�̉E����荶�̂Ƃ�
	if (pl.x+ps.x <= ol.x+os.x)
	{
		hit_r = true;
	}
	
	//�c����
	//�v���C���[�̏㑤���X�e�[�W�̏㑤��艺�̂Ƃ�
	if (pl.y-ps.y >= ol.y-os.y)
	{
		hit_u = true;
	}
	//�v���C���[�̉������X�e�[�W�̉�������̂Ƃ�
	if (pl.y+ps.y <= ol.y+os.y)
	{
		hit_d = true;
	}

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
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT)) && hit_l != false )
	{
		velocity.x += -5.0f;

		//�v���C���[�摜���������ɂ���
		move_image = LEFT;
		image = animation[10];
	}
	if ((InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT)) && hit_r != false)
	{
		velocity.x += 5.0f;

		//�v���C���[�摜���E�����ɂ���
		move_image = RIGHT;
		image = animation[15];
	}

	//�㉺�ړ�
	if ((InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP)) && hit_u != false)
	{
		velocity.y += -5.0f;

		//�v���C���[�摜���������ɂ���
		move_image = BACK;
		image = animation[2];
	}
	if ((InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN)) && hit_d != false)
	{
		velocity.y += 5.0f;

		//�v���C���[�摜��O�����ɂ���
		move_image = FRONT;
		image = animation[5];
	}
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
		if (limit_hp > 0)
		{
			limit_hp--;
		}
		else
		{
			hp--;
		}
		
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
}

void Player::Ultimate()
{
	limit_hp = 3;
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
		case FRONT:
			//�摜�̐؂�ւ�
			if (image == animation[5])
			{
				image = animation[7];
			}
			else
			{
				image = animation[5];
			}
			break;
			
		case BACK:
			//�摜�̐؂�ւ�
			if (image == animation[0])
			{
				image = animation[2];
			}
			else
			{
				image = animation[0];
			}
			break;
			
		case LEFT:
			//�摜�̐؂�ւ�
			if (image == animation[10])
			{
				image = animation[12];
			}
			else
			{
				image = animation[10];
			}
			break;
			
		case RIGHT:
			//�摜�̐؂�ւ�
			if (image == animation[15])
			{
				image = animation[17];
			}
			else
			{
				image = animation[15];
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

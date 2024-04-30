#include "Player.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
Player::Player() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Player::~Player()
{}

//����������
void Player::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("resource/images/tri-pilot1.png");
	animation[1] = LoadGraph("resource/images/tri-pilot2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�g���p�C���b�g�̉摜������܂���\n");
	}

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
	DrawRotaGraphF(location.x, location.y, 0.4, radian, image, TRUE, filp_flag);

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
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
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
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		//velocity.x += 5.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x += 0.0f;
	}

	//�㉺�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		//velocity.y += -5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		//velocity.y += 5.0f;
	}
	else
	{
		velocity.y += 0.0f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
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

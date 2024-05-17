#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../../Scenes/Main.h"
#include "../Player/Player.h"
#include"DxLib.h"


//�ړ��̑���
Vector2D velocity;
int hit = 0;

//�X�e�[�W���
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };


//�R���X�g���N�^
Stage::Stage()
{
	type = 0;
}

//�f�X�g���N�^
Stage::~Stage()
{

}

//����������
void Stage::Initialize()
{
	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 500.0;

	//�����摜�̐ݒ�
	image = NULL;

	type = Main::GetStageType();
}

//�X�V����
void Stage::Update()
{
	//�ړ�����
	Movement();

}

//�`�揈��
void Stage::Draw() const
{
	//�摜�̕`��
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	DrawFormatString(10, 200, 0xffffff, "%d", hit);

	__super::Draw();
}

//�I��������
void Stage::Finalize()
{
	
}

//�����蔻��ʒm����
void Stage::OnHitCollision(GameObject* hit_object,int i)
{
	//�����������̏���
	hit = i;
}

//�ʒu���擾����
Vector2D Stage::GetLocation() const
{
	return this->location;
}

//�傫���擾����
Vector2D Stage::Getscale() const
{
	return this->scale;
}

//�ʒu���ݒ菈��
void Stage::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�X�e�[�W���擾����
int Stage::GetStage(int i,int j)
{
	return stage[i][j];
}

//�X�e�[�W���ݒ菈��
void Stage::SetStage()
{

}

//�ړ�����
void Stage::Movement()
{
	velocity = 0.0f;

	if (hit == 0)
	{
		//���E�ړ�
		if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
		{
			velocity.x += 5.0f;
		}
		else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			velocity.x += -5.0f;
		}
		else
		{
			velocity.x += 0.0f;
		}

		//�㉺�ړ�
		if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
		{
			velocity.y += 5.0f;
		}
		else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
		{
			velocity.y += -5.0f;
		}
		else
		{
			velocity.y = 0.0f;
		}
	}
	else
	{
		velocity = 0;
	}

	location += velocity;
}


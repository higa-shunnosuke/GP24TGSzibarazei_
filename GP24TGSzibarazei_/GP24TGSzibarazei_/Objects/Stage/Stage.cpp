#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../../Scenes/Main.h"
#include "../Player/Player.h"
#include"DxLib.h"


//�ړ��̑���
Vector2D velocity;

//�X�e�[�W���
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };

//�R���X�g���N�^
Stage::Stage() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	color = 0xffffff;
	type = 0;
}

//�f�X�g���N�^
Stage::~Stage()
{}

//����������
void Stage::Initialize()
{
	//�摜�̓ǂݍ���
	//animation[0] = loadgraph("resource/images/tri-pilot1.png");
	//animation[1] = loadgraph("resource/images/tri-pilot2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�X�e�[�W�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 50.0;

	//�����摜�̐ݒ�
	image = animation[0];

	type = Main::GetStageType();
}

//�X�V����
void Stage::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	//AnimeControl();
}

//�`�揈��
void Stage::Draw() const
{
	//�摜�̕`��
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	__super::Draw();
}

//�I��������
void Stage::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Stage::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += -5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity.x += 5.0f;
	}

	//�㉺�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity.y += -5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += 5.0f;
	}
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

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += +5.0f;
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
		velocity.y += +5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += -5.0f;
	}
	else
	{
		velocity.y += 0.0f;
	}

	////�ǂ̏���
	//if (location.x < (640.0f - scale.x + 25.0f + scale.x / 2))
	//{	//���̕�
	//	velocity.x += 0.0f;
	//	location.x = 640 - scale.x + 25 + scale.x / 2.0f;
	//}
	//else if (location.x > (640.0f + scale.x - 25.0f - scale.x / 2.0f))
	//{	//�E�̕�
	//	velocity.x = 0.0f;
	//	location.x = 640.0f + scale.x - 25.0f - scale.x / 2.0f;
	//}
	//if (location.y < (360.0f - scale.y + 25.0f + scale.y / 2.0f))
	//{	//��̕�
	//	velocity.y = 0.0f;
	//	location.y = 360.0f - scale.y + 25.0f + scale.y / 2.0f;
	//}
	//else if (location.y > (360.0f + scale.y - 25.0f - scale.y / 2.0f))
	//{	//���̕�
	//	velocity.y = 0.0f;
	//	location.y = 360.0f + scale.y - 25.0f - scale.y / 2.0f;
	//}

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
//void Stage::AnimeControl()
//{
//	//�t���[���J�E���g�����Z����
//	animation_count++;
//
//	//�U�O�t���[���ڂɓ��B������
//	if (animation_count >= 60)
//	{
//		//�J�E���g�̃��Z�b�g
//		animation_count = 0;
//
//		//�摜�̐؂�ւ�
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}

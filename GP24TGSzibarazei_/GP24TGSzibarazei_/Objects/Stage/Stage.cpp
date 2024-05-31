#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include "../../Scenes/Main.h"
#include"DxLib.h"

//�X�e�[�W���
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };

//�����̐�
int room_count = 0;

//�R���X�g���N�^
Stage::Stage()
{
	type = 0;
	move = Vector2D(0.0f);
	color = 0xffffff;
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
	scale = 100.0;

	//�����摜�̐ݒ�
	image = NULL;

	type = Main::GetStageType();

	move = Vector2D(0.0f);

	color = 0xffffff;
}

//�X�V����
void Stage::Update()
{
	move = Player::GetVelocity();

	location -= move;

	color = 0xffffff;

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		SetStage();
	}
}

//�`�揈��
void Stage::Draw() const
{
	//�摜�̕`��
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		color,TRUE);

	DrawFormatString(10, 110, 0xffff00, "%d", room_count);

	__super::Draw();
}

//�I��������
void Stage::Finalize()
{
	
}

//�����蔻��ʒm����
void Stage::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	color = 0x00ff00;

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
	//�J�E���g
	int i=0;
	int j=0;

	//�����̐������߂�
	room_count = GetRand(2) + 4;

	//�X�e�[�W��������������
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (room_count > 0)
			{
				stage[i][j] = 0;
			}
		}
	}
	
	while (true)
	{
		//�{�[�i�X�����̐�
		int s_room = 0;	
		//
		int rand = GetRand(100) % 4;

		if (room_count > 0)
		{
			
			if (rand == 3)
			{
				s_room++;
			}
			if (rand != 0 && s_room < 1)
			{
				stage[i][j] = rand;
				room_count--;
				j++;
			}
		}
	}
}

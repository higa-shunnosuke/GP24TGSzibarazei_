#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include "../../Scenes/Main.h"
#include"DxLib.h"

typedef enum StageType {
	Empty,
	Respawn,
	Normal,
	Boss,
	Special,
}state;

//�X�e�[�W���
int stage[9] = {
	0,0,0,
	0,0,0,
	0,0,0 };

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
void Stage::Initialize(int stage_type)
{
	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 100.0;

	//�����摜�̐ݒ�
	//image = LoadGraph("Resource/images/stage/grass_block.png");

	type = Main::GetStageType();

	move = Vector2D(0.0f);

	color = 0xffffff;

	//if (image == -1)
	//{
	//	throw("block�̉摜������܂���\n");
	//}
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
int Stage::GetStage(int i)
{
	return stage[i];
}

//�X�e�[�W���ݒ菈��
int Stage::SetStage()
{
	//�J�E���g
	int i = 0;
	int j = 0;
	int count = 0;

	//
	state e, r, n, b, s;
	e = Empty;
	r = Respawn;
	n = Normal;
	b = Boss;
	s = Special;

	//���X�|�[�������̈ʒu������
	int r_room = GetRand(8);

	//�����̐������߂�
	room_count = GetRand(2) + 4;

	//�X�e�[�W��������������
	for (i = 0; i < 8; i++)
	{
		if (count != r_room)
		{
			stage[i] = e;
			count++;
		}
		else
		{
			stage[i] = r;
			count++;
		}
	}

	return r_room;
}

#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include "../../Scenes/Main.h"
#include"DxLib.h"


//�ړ��̑���
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
	move = Vector2D(0.0f);
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
	scale = 50.0;

	//�����摜�̐ݒ�
	image = NULL;

	type = Main::GetStageType();

	move = Vector2D(0.0f);

}

//�X�V����
void Stage::Update()
{
	move = Player::GetVelocity();

	location -= move;

}

//�`�揈��
void Stage::Draw() const
{
	//�摜�̕`��
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	DrawFormatString(10, 200, 0xffffff, "%f", move.x);
	DrawFormatString(10, 220, 0xffffff, "%f", move.y);

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
	//hit = i;
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

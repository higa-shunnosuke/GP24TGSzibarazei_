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
}

//�`�揈��
void Stage::Draw() const
{
	//�摜�̕`��
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		color,TRUE);

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

}

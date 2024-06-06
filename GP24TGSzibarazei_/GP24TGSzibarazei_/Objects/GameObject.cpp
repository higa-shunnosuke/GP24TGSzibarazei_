#include "GameObject.h"
#include "../Scenes/SceneBase.h"
#include"DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	radian(0.0),
	image(0),
	sound(0)
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize(int type)
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{
	//�f�o�b�N�p
#if _DEBUG
//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (scale / 2.0f);
	Vector2D box_collision_upper_right = location + (scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void GameObject::Finalize()
{

}


bool GameObject::HitCheck(const GameObject* gameobject) const
{
	bool ret = false; //�Ԃ�l

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (scale.x / 2);
	my_y[0] = location.y - (scale.y / 2);
	my_x[1] = my_x[0] + scale.x;
	my_y[1] = my_y[0] + scale.y;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = gameobject->GetLocation().x - (gameobject->Getscale().x / 2);
	sub_y[0] = gameobject->GetLocation().y - (gameobject->Getscale().y / 2);
	sub_x[1] = sub_x[0] + gameobject->Getscale().x;
	sub_y[1] = sub_y[0] + gameobject->Getscale().y;

	if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
		&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�傫���擾����
Vector2D GameObject::Getscale() const
{
	return this->scale;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void GameObject::SetSceneBase(SceneBase* scenebase)
{
	SB = scenebase;
}

//�����蔻��̑傫�����擾����
Vector2D GameObject::GetBoxSize() const
{
	return scale;
}

//�I�u�W�F�N�g�̃^�C�v���擾����
int GameObject::GetType() const
{
	return type;
}
#include "GameObject.h"

//�R���X�g���N�^
GameObject::GameObject() :
	radian(0.0),
	image(0),
	sound(0)
{}

//�f�X�g���N�^
GameObject::~GameObject()
{}

//����������
void GameObject::Initialize()
{}

//�X�V����
void GameObject::Update()
{}

//�`�揈��
void GameObject::Draw() const
{}

//�I��������
void GameObject::Finalize()
{}


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
Location GameObject::GetLocation() const
{
	return this->location;
}

//�傫���擾����
Scale GameObject::Getscale() const
{
	return this->scale;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Location& location)
{
	this->location = location;
}
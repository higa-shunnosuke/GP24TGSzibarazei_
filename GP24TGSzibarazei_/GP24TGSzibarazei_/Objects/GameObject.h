#pragma once

#include"../Utility/Vector2D.h"

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;	//�ʒu���
	Vector2D scale;		//�傫��
	double radian;		//����
	int image;			//�`�悷��摜
	int sound;			//�Đ����鉹��

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//����������
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�I��������

	//�q�b�g�`�F�b�N
	bool HitCheck(const class GameObject* GemeObject)const;
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);
	//�ʒu���擾����
	virtual Vector2D GetLocation() const;
	//�傫���擾����
	virtual Vector2D Getscale() const;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location);
	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;
};


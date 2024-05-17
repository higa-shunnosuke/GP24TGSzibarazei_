#pragma once

#include"../GameObject.h"

class Enemy :public GameObject
{
private:
	int animation[15];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������(�A�C�h�����O�p)
	int HP;						//HitPoint(�̗�)
	float AS;					//AtackSpeed(�U�����x)
	int ATK;					//Attack(�U����)
	int Speed;					//AGL(���x)
	int AL;						//AttackLenge(�U���͈�)



public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;	//����������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object,int i) override;
	//�ʒu���擾����
	virtual Vector2D GetLocation() const override;
	//�傫���擾����
	virtual Vector2D Getscale() const override;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();

};
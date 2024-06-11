#pragma once

#include"Enemy.h"

class Enemy_Attack : public GameObject
{

private:
	int animation[25];			//�A�j���[�V�����摜
	int anim;
	int animation_count;		//�A�j���[�V��������(�A�C�h�����O�p)
	float AS;					//AtackSpeed(�U�����x)
	int ATK;					//Attack(�U����)
	Vector2D Speed;				//AGL(���x)
	int AL;						//AttackLenge(�U���͈�)
	Vector2D location;
	float scale;
public:
	Enemy_Attack();
	~Enemy_Attack();

	virtual void Initialize(int enemy_type) override;	//����������
	virtual void Attack();				//�U������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I������
	virtual void Movement();

	//�G�l�~�[�̏����󂯎��
	virtual bool SetEnemy(int ATK,int AL,float AS, Vector2D loc);
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) ;
	//�ʒu���擾����
	virtual Vector2D GetLocation() const ;
	//�傫���擾����
	virtual Vector2D Getscale() const ;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location) ;
	//�^�C�v�擾����
	virtual int GetType() const override;
};


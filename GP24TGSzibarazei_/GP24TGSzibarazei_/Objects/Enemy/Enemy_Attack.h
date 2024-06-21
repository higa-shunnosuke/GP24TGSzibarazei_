#pragma once

#include"Enemy.h"
#include"../Player/Player.h"
#include"../DeleteClass.h"

class Enemy_Attack : public DeleteClass
{

private:
	class Player* player;
	class Enemy* enemy;
	int animation[20];			//�A�j���[�V�����摜
	int anim;
	int animation_count;		//�A�j���[�V��������(�A�C�h�����O�p)
	float AS;					//AtackSpeed(�U�����x)
	int ATK;					//Attack(�U����)
	Vector2D Speed;				//AGL(���x)
	int AL;						//AttackLenge(�U���͈�)
	float radian;
	bool isHit;
public:
	Enemy_Attack();
	~Enemy_Attack();

	virtual void Initialize(int enemy_type) override;	//����������
	virtual void Attack();				//�U������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I������
	virtual void Movement();
	virtual void AnimControl();


	//�G�l�~�[�̏����󂯎��
	virtual bool SetEnemy(int ATK,int AL,float AS, Vector2D loc,Player* p,Enemy* e);
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	//�ʒu���擾����
	virtual Vector2D GetLocation() const override;
	//�傫���擾����
	virtual Vector2D Getscale() const override;
	////�^�C�v�擾����
	//virtual int GetType() const override;
};


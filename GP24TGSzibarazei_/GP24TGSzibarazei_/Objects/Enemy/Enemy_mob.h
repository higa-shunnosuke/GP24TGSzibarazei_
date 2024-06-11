#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"

class Enemy_mob:public GameObject
{
private:
	int animation[20];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������(�A�C�h�����O�p)
	int HP;						//HitPoint(�̗�)
	float AS;					//AtackSpeed(�U�����x)
	int ATK;					//Attack(�U����)
	int Speed;					//AGL(���x)
	int AL;						//AttackLenge(�U���͈�)
	int ET;						//EnemyType(�G�̎�ނ�I������)
	bool isBoss;				//���̓G���{�X���ǂ������m�F����

public:
	Enemy_mob();
	~Enemy_mob();

	virtual void Initialize(int enemy_type) override;	//����������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	//�ʒu���擾����
	virtual Vector2D GetLocation() const override;
	//�傫���擾����
	virtual Vector2D Getscale() const override;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location) override;
	//�^�C�v�擾����
	virtual int GetType() const override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();

};
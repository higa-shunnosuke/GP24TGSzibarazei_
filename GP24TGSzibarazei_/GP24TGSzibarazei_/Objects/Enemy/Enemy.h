#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"

class Enemy :public GameObject
{
private:
	int animation[20];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������(�A�C�h�����O�p)
	int HP;						//HitPoint(�̗�)
	float AS;					//AtackSpeed(�U�����x)
	int ATK;					//Attack(�U����)
	Vector2D Speed;				//AGL(���x)
	int AL;						//AttackLenge(�U���͈�)
	int ET;						//EnemyType(�G�̎�ނ�I������)
	bool isBoss;				//���̓G���{�X���ǂ������m�F����
	Player* player;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;	//����������
	virtual void Attack();				//�U������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�v���C���[�̃|�C���^���󂯎��
	virtual void SetPlayer(class Player* player);
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
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
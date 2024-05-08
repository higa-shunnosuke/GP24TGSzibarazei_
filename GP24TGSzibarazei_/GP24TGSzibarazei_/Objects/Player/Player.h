#pragma once

#include"../GameObject.h"

class Player :public GameObject
{
private:
	int hp;               //�̗�
	int mp;               //�}�W�b�N�p���[
	int ult_active;       //�A���e�B���b�g�g�p�\���
	int animation[8];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	int move_image;             //�i�s�����ɑΉ�����摜�̓ǂݍ���
	int flip_flag;				//���]�t���O

public:
	Player();
	~Player();

	virtual void Initialize() override;	//����������
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

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();
	//�U������
	void Atack();

};


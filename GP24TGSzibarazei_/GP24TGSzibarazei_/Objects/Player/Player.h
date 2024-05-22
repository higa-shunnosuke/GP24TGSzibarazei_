#pragma once

#include"../GameObject.h"

class Player :public GameObject
{
private:
	int hp;               //�̗�
	int max_hp;           //�ő�̗�
	int mp;               //�}�W�b�N�p���[
	int level;            //�v���C���[�̃��x��
	int exp;              //�o���l
	int max_exp;          //���x���A�b�v�ɕK�v�Ȍo���l�̗�
	int ult_count;
	int ult_active;       //�A���e�B���b�g�g�p�\���
	int animation[30];	  //�A�j���[�V�����摜
	int animation_count;  //�A�j���[�V��������
	int move_image;		  //�i�s�����ɑΉ�����摜�̓ǂݍ���
	int ui_image[8];      //HP/MP����UI�̉摜
	int flip_flag;	      //���]�t���O
	int move_flag;        //�ړ��\��Ԃ�(0=�ړ��s��,(1=�ړ��\)

public:
	Player();
	~Player();

	virtual void Initialize() override;	//����������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�����蔻��ʒm����(�q�b�g��)
	virtual void OnHitCollision(GameObject* hit_object,int i) override;
	//�ʒu���擾����
	 virtual Vector2D GetLocation() const override;
	//�傫���擾����
	virtual Vector2D Getscale() const override;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location) override;

	//�ړ������擾����
	static Vector2D GetVelocity();

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();
	//�U������
	void Atack();
	//�A���e�B���b�g����
	void Ultimate();
	//�o���l�E���x���A�b�v�̏���
	void LevelUp(int get_exp);
	//�p�b�V�u�X�L���l������
	void AcquisitionPassive();
};


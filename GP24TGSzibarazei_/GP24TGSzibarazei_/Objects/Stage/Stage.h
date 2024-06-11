#pragma once
#include"../GameObject.h"

class Stage :public GameObject
{
private:
	Vector2D move;		//�ړ�����

	unsigned int color;	//�u���b�N�̐F


public:
	Stage();
	~Stage();

	virtual void Initialize(int stage_type) override;	//����������
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
	static int GetStage(int i);
	static int SetStage();

private:
};


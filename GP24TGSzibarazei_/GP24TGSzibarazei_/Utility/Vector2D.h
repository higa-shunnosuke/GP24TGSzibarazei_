#pragma once
//�Q�����x�N�g���p�N���X
class Vector2D
{
public:
	float x;	//x����
	float y;	//y����

public:
	//�R���X�g���N�^
	Vector2D();
	//�����t���R���X�g���N�^(float scalar)
	Vector2D(float scalar);
	//�����t���R���X�g���N�^(float mx,float my)
	Vector2D(float mx, float my);
	//�f�X�g���N�^
	~Vector2D();

public:
	//���:���Z�q�I�[�o�[���[�h
	Vector2D& operator=(const Vector2D& location);

	//���Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator + (const Vector2D& location) const;
	//���Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator += (const Vector2D& location);

	//���Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator - (const Vector2D& location) const;
	//���Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator -= (const Vector2D& location);

	//��Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator * (const float& scalar) const;
	//��Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator * (const Vector2D& location) const;
	//��Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator *= (const float& scalar);
	//��Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator *= (const Vector2D& location);

	//���Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator / (const float& scalar) const;
	//���Z:���Z�q�I�[�o�[���[�h
	const Vector2D operator / (const Vector2D& location) const;
	//���Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator /= (const float& scalar);
	//���Z���:���Z�q�I�[�o�[���[�h
	Vector2D& operator /= (const Vector2D& location);

	//�����^�f�[�^�ɕϊ�
	void ToInt(int* x, int* y) const;
};
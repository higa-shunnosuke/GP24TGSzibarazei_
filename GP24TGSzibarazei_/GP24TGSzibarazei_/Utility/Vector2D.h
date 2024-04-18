#pragma once
//２次元ベクトル用クラス
class Vector2D
{
public:
	float x;	//x成分
	float y;	//y成分

public:
	//コンストラクタ
	Vector2D();
	//引数付きコンストラクタ(float scalar)
	Vector2D(float scalar);
	//引数付きコンストラクタ(float mx,float my)
	Vector2D(float mx, float my);
	//デストラクタ
	~Vector2D();

public:
	//代入:演算子オーバーロード
	Vector2D& operator=(const Vector2D& location);

	//加算:演算子オーバーロード
	const Vector2D operator + (const Vector2D& location) const;
	//加算代入:演算子オーバーロード
	Vector2D& operator += (const Vector2D& location);

	//減算:演算子オーバーロード
	const Vector2D operator - (const Vector2D& location) const;
	//減算代入:演算子オーバーロード
	Vector2D& operator -= (const Vector2D& location);

	//乗算:演算子オーバーロード
	const Vector2D operator * (const float& scalar) const;
	//乗算:演算子オーバーロード
	const Vector2D operator * (const Vector2D& location) const;
	//乗算代入:演算子オーバーロード
	Vector2D& operator *= (const float& scalar);
	//乗算代入:演算子オーバーロード
	Vector2D& operator *= (const Vector2D& location);

	//除算:演算子オーバーロード
	const Vector2D operator / (const float& scalar) const;
	//除算:演算子オーバーロード
	const Vector2D operator / (const Vector2D& location) const;
	//除算代入:演算子オーバーロード
	Vector2D& operator /= (const float& scalar);
	//除算代入:演算子オーバーロード
	Vector2D& operator /= (const Vector2D& location);

	//整数型データに変換
	void ToInt(int* x, int* y) const;
};
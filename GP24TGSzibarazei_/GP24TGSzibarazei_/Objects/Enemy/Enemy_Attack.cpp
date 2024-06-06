#include "Enemy_Attack.h"
#include"DxLib.h"


static int type;

Enemy_Attack::Enemy_Attack():AL(-1),ATK(-1),AS(-1.0f),scale(1.0f)
{
	// anim = LoadGraph("Resource/images/打撃エフェクト.mp4");
}

Enemy_Attack::~Enemy_Attack()
{
}

bool Enemy_Attack::SetEnemy(int ATK, int AL, float AS ,Vector2D loc)
{
	if (ATK == -1 || AL == -1 || AS == -1.0f){
		return false;
	}
	this->ATK = ATK;
	this->AL = AL;
	this->AS = AS;
	this->location = loc;

	return true;
}

void Enemy_Attack::OnHitCollision(GameObject* hit_object)
{
}

Vector2D Enemy_Attack::GetLocation() const
{
	return Vector2D();
}

Vector2D Enemy_Attack::Getscale() const
{
	return Vector2D();
}

void Enemy_Attack::SetLocation(const Vector2D& location)
{
}

void Enemy_Attack::Initialize(int enemy_type)
{
}

void Enemy_Attack::Attack()
{
}

void Enemy_Attack::Update()
{
	Draw();

}

void Enemy_Attack::Draw() const
{
	// 動画を指定した位置とサイズで描画
	DrawExtendGraphF(location.x, location.y, location.x + 50, location.y + 50, anim, TRUE);

	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (scale / 2.0f);
	Vector2D box_collision_upper_right = location + (scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy_Attack::Finalize()
{
}

//ステージのタイプ取得処理
int Enemy_Attack::GetType() const
{
	return type;
}
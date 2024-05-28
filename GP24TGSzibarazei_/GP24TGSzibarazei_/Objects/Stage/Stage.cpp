#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include "../../Scenes/Main.h"
#include"DxLib.h"


//ステージ情報
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };


//コンストラクタ
Stage::Stage()
{
	type = 0;
	move = Vector2D(0.0f);
	color = 0xffffff;
}

//デストラクタ
Stage::~Stage()
{

}

//初期化処理
void Stage::Initialize()
{
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 100.0;

	//初期画像の設定
	image = NULL;

	type = Main::GetStageType();

	move = Vector2D(0.0f);

	color = 0xffffff;
}

//更新処理
void Stage::Update()
{
	move = Player::GetVelocity();

	location -= move;

	color = 0xffffff;
}

//描画処理
void Stage::Draw() const
{
	//画像の描画
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		color,TRUE);

	__super::Draw();
}

//終了時処理
void Stage::Finalize()
{
	
}

//当たり判定通知処理
void Stage::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	color = 0x00ff00;

}

//位置情報取得処理
Vector2D Stage::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D Stage::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void Stage::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//ステージ情報取得処理
int Stage::GetStage(int i,int j)
{
	return stage[i][j];
}

//ステージ情報設定処理
void Stage::SetStage()
{

}

#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../Player/Player.h"
#include "../../Scenes/Main.h"
#include"DxLib.h"

typedef enum StageType {
	Empty,
	Respawn,
	Normal,
	Boss,
	Special,
}state;

//ステージ情報
int stage[9] = {
	0,0,0,
	0,0,0,
	0,0,0 };

//部屋の数
int room_count = 0;
int r_room;

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
void Stage::Initialize(int stage_type)
{
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 100.0;

	//初期画像の設定
	//image = LoadGraph("Resource/images/stage/grass_block.png");

	type = stage_type;

	move = Vector2D(0.0f);

	if (type == 0)
	{
		color = 0xffffff;
	}
	else if(type == 1)
	{
		color = 0x000000;
	}

	//if (image == -1)
	//{
	//	throw("blockの画像がありません\n");
	//}
}

//更新処理
void Stage::Update()
{
	move = Player::GetVelocity();

	location -= move;

	if (type == 0)
	{
		color = 0xffffff;
	}
	else if (type == 1)
	{
		color = 0x000000;
	}

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		SetStage();
	}
}

//描画処理
void Stage::Draw() const
{
	//画像の描画
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		color,TRUE);

	DrawFormatString(upper_left.x, upper_left.y, 0x00ff00, "%d", type);

	DrawFormatString(10, 130, 0xffff00, "%d", room_count);
	DrawFormatString(10, 150, 0xffff00, "%d", r_room);

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

//ステージのタイプ取得処理
int Stage::GetType() const
{
	return type;
}

//ステージ情報取得処理
int Stage::GetStage(int i)
{
	return stage[i];
}

//ステージ情報設定処理
int Stage::SetStage()
{
	//カウント
	int i = 0;
	int j = 0;
	int count = 0;

	//
	state e, r, n, b, s;
	e = Empty;
	r = Respawn;
	n = Normal;
	b = Boss;
	s = Special;

	//リスポーン部屋の位置を決定
	r_room = GetRand(8);

	//部屋の数を決める
	room_count = GetRand(2) + 4;

	//ステージ情報を初期化する
	for (i = 0; i < 9; i++)
	{
		if (count != r_room)
		{
			stage[i] = e;
			count++;
		}
		else
		{
			stage[i] = r;
			count++;
		}
	}

	return r_room;
}

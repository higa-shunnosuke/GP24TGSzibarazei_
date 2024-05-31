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

//部屋の数
int room_count = 0;

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

	DrawFormatString(10, 110, 0xffff00, "%d", room_count);

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
	//カウント
	int i=0;
	int j=0;

	//部屋の数を決める
	room_count = GetRand(2) + 4;

	//ステージ情報を初期化する
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (room_count > 0)
			{
				stage[i][j] = 0;
			}
		}
	}
	
	while (true)
	{
		//ボーナス部屋の数
		int s_room = 0;	
		//
		int rand = GetRand(100) % 4;

		if (room_count > 0)
		{
			
			if (rand == 3)
			{
				s_room++;
			}
			if (rand != 0 && s_room < 1)
			{
				stage[i][j] = rand;
				room_count--;
				j++;
			}
		}
	}
}

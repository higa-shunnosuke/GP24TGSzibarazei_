#pragma once


//ステージ用クラス
class Stage
{
private:
	int image[4];		//画像
	int stage[];		//ステージ

public:
	Stage();
	~Stage();

	virtual void Initialize();	//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//終了時処理

private:
	void CreateStage();			//ステージ生成
};


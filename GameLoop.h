#pragma once
#include"stdafx.h"
#include"GameScene.h"
#include"ImageLoader.h"
#include"KeyState.h"
/*ゲームのメイン部分*/
class GameLoop
{
private:
	/*時間計測用*/
	double draw_time;
	double update_time;
	int init_time;
	int elasped_time;
	/**/
	int m_StartTime;						//測定開始時刻
	int m_Count;							//カウンタ
	float m_Fps;							//fps
	GameScene* m_Scene;						//ゲームの処理そのもの
	KeyState* m_Key;						//キー入力情報
	bool m_game_quit;						//ゲームが終了かどうかのフラグ
	ImageLoader* m_loader;					//ゲーム内に画像を保管するローダー
public:
	GameLoop(void);
	~GameLoop(void);
	void init(GameScene::MODE mode);		//モードを指定してゲームを初期化
	void update();							//フレーム開始時のアップデート
	void draw();							//フレーム終了時に呼び出す描画関数
	bool IsQuit(){return m_game_quit;}		//ゲームが終了状態かどうかの取得
	void wait();
};
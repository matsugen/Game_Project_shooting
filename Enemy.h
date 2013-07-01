#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
private:
	SpriteNode* m_icon;
	int m_Emergency_interval;	//初期化から出動までの時間
	double m_speed;				//敵の移動速度。乱数で出力
public:
	Enemy(void);
	~Enemy(void);	
	void update(KeyState* Key,ImageLoader* loader);							//更新関数:派生クラスのprivateに各種更新をまとめた関数をつくり、それを順に実行する
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);	//アクター初期化関数
	void Hit();																//ゲームシーン側で判定が衝突した場合に呼び出される。
	bool Kill();															//enemyは死んだ時、オブジェクト以外をすべて初期化する。
	void On();
};


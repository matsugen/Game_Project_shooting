#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
private:
	SpriteNode* m_icon;
	int m_Emergency_interval;	//初期化から出動までの時間
	int m_alpha;				//敵アイコンの透明度。死ぬときに消えていき、0になると消滅
	double m_speed;				//敵の移動速度。乱数で出力
	void Launch();
	void Move();
	void Death();
public:
	Enemy(void);
	~Enemy(void);	
	void update(KeyState* Key,ImageLoader* loader);							//更新関数:派生クラスのprivateに各種更新をまとめた関数をつくり、それを順に実行する
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);	//アクター初期化関数
	void Hit();																//ゲームシーン側で判定が衝突した場合に呼び出される。
	bool Kill();															//enemyは死んだ時、オブジェクト以外をすべて初期化する。
	void On();
};


#pragma once
#include"stdafx.h"
#include "Actor.h"
#include "Bullet.h"
#include"Misile.h"
#include"ImageLoader.h"
#include"DrawSystem.h"
//#include"ActorManager.h"
class Player :
	public Actor
{
public:
	enum BULLET_TYPE{
		VULCAN,
		MISILE,
		SHOTGUN
	};
private:
	/*移動関係の変数*/
	int m_d;							//キャラの方向
	int m_walk_time;
	int m_freeze_time;					//動けない時間
	/*攻撃関係の変数*/
	int m_attack_num;					//攻撃弾数の個数
	Player::BULLET_TYPE m_type;		//使う弾の種類
	double m_angle;						//武器の角度
	/*表示関係の変数*/
	SpriteNode* m_icon;					//弾アイコン
	/*Playerの動きを関数化*/
	void Move(KeyState* Key);			//キャラの座標を移動
	void Attack(KeyState* Key);			//リターンキーかスペースキーが押された時、死亡状態でなく、且つ実行状態でない弾丸を一つ実行状態にして終了する
	void Weapon_Change(KeyState* Key);
	/*Playerが所持する弾のアクター*/
	std::vector<Bullet*> m_bullet;		//弾アクターの存在確認用ベクター
	std::vector<Misile*> m_misile;		//弾アクターの存在確認用ベクター
public:
	Player(void);
	~Player(void);
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//プレイヤーの状態初期化(主に描画)
	void update(KeyState* Key,ImageLoader* loader);//更新関数
};


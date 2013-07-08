#pragma once
#include"stdafx.h"
class Actor;
class DrawSystem;
class SpriteNode;
namespace OWNER{
enum OWNER{
	NONE=-1,
	PLAYER,
	BULLET,
	ENEMY};
}

typedef struct collision_option{//collisionのオプションを設定
	double m_x,m_y,m_w,m_h;		//判定矩形の左上の相対座標とその大きさ
	double abs_x,abs_y;			//左上座標の絶対座標
	bool hit_flg;				//ヒットしたかどうかの判断
	bool effective;				//この判定が有効かどうか
	OWNER::OWNER owner;				//この判定の所持者名
}C_OPTION;
class Collision
{
private:
	Actor* m_owner;									//このcollisionを所持するアクターのポインタ
	collision_option m_option;						//collisionのステータス
#ifndef NDEBUG
	DrawSystem* m_drawsystem;
	SpriteNode* m_box;
#endif
public:
	Collision(void);
	Collision(Actor* owner,collision_option option,DrawSystem* ds);
	~Collision(void);
	void Hit();										//hit_flgをtrueにする
	C_OPTION Get_Option();							//Collisionの内容を取得。
	void Set_Option(C_OPTION option);
	void update();									//このcollisionを所持するActorに合わせて動く
	void On();										//このCollisionを有効にする
	void Off();										//このCollisionを無効にする。ヒット判定は変えない
	void Reset();									//Collisionが有効化どうかとヒットした判定をfalseにする。
};

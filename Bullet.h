#pragma once
#include"stdafx.h"
#include"Actor.h"
/*弾丸クラス*/
/*
親を持ちうるクラスで、発射時(生成時)飲み親に追随する。
そのためコンストラクタに親となるアクターを引数に持つ者が存在(new Bullet(this)などで親アクターは自身を引数とする)する。
*/

class Bullet :
	public Actor
{
private:
	SpriteNode* m_icon;	//弾丸のアイコン
	void Move();		//弾丸の座標移動だけを行う。
public:
	Bullet(void);
	Bullet(Actor* parent);
	~Bullet(void);
	void update(KeyState* Key,ImageLoader* loader);//更新関数
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//アクター初期化関数
	void Hit();
	bool Kill();
	void On();
	void Off();
};


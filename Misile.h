#pragma once
class Misile:
	public Actor
{
private:
	SpriteNode* m_icon;	//弾丸のアイコン
	void Move();		//弾丸の座標移動だけを行う。
public:
	Misile(void);
	Misile(Actor* parent);
	~Misile(void);
	void update(KeyState* Key,ImageLoader* loader);//更新関数
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//アクター初期化関数
	void Hit();
	bool Kill();
	void On();
	void Off();
};


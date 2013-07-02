#pragma once
class Misile:
	public Actor
{
private:
	double m_move_time;	//ミサイルの出現からの時間
	double m_angle;		//ミサイルの方向
	SpriteNode* m_icon;	//弾丸のアイコン
	void Move();		//弾丸の座標移動だけを行う。
	double Misile_Speed();
	SpriteNode* m_dbg;
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


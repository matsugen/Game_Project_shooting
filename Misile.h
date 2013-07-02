#pragma once
class Misile:
	public Actor
{
private:
	double m_move_time;	//ミサイルの出現からの時間
	double m_angle;		//ミサイルの方向
	SpriteNode* m_icon;	//弾丸のアイコン
	bool m_bomb_flg;	//ミサイルがあたった時の爆発のフラグ
	int m_bomb_time;	//爆発の時間
	void Move();		//弾丸の座標移動だけを行う。
	double Misile_Speed();
	void Bomb();		//爆風を留める。
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


#pragma once
#include"stdafx.h"
#include"KeyState.h"
#include"DrawSystem.h"
#include"ImageLoader.h"
#include"ActorManager.h"
/*プレイヤーやCPUの基底クラス*/
class Actor
{
protected:
	bool m_death_flg;											//アクターの死状態
	bool m_init_flg;											//このアクターが初期化済みかどうかのフラグ。ActorManagerにて初期化されていなければ初期化を行う
	bool m_launch_flg;											//このアクターが実行状態であるかのフラグ。On,Off関数によって管理する
	Actor* m_Parent;											//アクターの親の存在を示す。
	ActorManager* m_manager;									//このアクターが登録されているアクターファクトリーを確保。これがないと子を生成する時面倒
	DrawSystem* m_drawsystem;									//このアクターに登録されるSpriteNodeを管理
	ImageLoader* m_loader;										//アクターのアイコンを持ってくるローダー
	double m_x,m_y;											//メインとなるスプライトの座標
#ifdef COLLISION
	std::vector<Collision*> m_collisions;						//ゲームによりCollisionの内容は変化するが、その定義時には必ず"Collision"で宣言すること。
#endif
	void Collision_update();
public:
	Actor(void);
	virtual ~Actor(void);
	virtual void update(KeyState* Key,ImageLoader* loader)=0;						//更新関数:派生クラスのprivateに各種更新をまとめた関数をつくり、それを順に実行する
	virtual void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager)=0;	//アクター初期化関数
	bool IsDeath(){return m_death_flg;}												//アクターの死状態を確認
	void Die(){m_death_flg=true;}
	bool Initialized(){return m_init_flg;}											//このアクターが初期化済みかどうかを確認
	void Ended_init(){m_init_flg=true;}
	bool Parent_Exist();															//このアクターに親がいるかどうかを確認
	double Get_X(){return m_x;}														//x座標取得
	double Get_Y(){return m_y;}														//y座標取得
	virtual bool Kill();															//アクターが死ぬ時の動作。これを定義してtrueを返すことでアクターの再利用を可能にする(new-deleteを減らす)
	virtual void On();																//アクターを実行状態に変化させる。その際に必要な初期化も行う
	virtual void Off();																//アクターを非実行状態に変化させる。
	bool Get_Launch_flg(){return m_launch_flg;}															//実行状態かどうかを確認する
#ifdef COLLISION
	std::vector<Collision*> Get_Collision();										//ゲームシーンが判定の処理を行うために使う。				
	void Add_Collision(C_OPTION option);											//オプションを作ってその下でCollisionを追加する。
	virtual void Hit();															//ゲームシーン側で判定が衝突した場合に呼び出される。
#endif
};


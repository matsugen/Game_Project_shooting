#include "stdafx.h"
#include "Actor.h"


Actor::Actor(void):
	m_death_flg(false),											//アクターの死状態
	m_init_flg(false),											//このアクターが初期化済みかどうかのフラグ。ActorManagerにて初期化されていなければ初期化を行う
	m_launch_flg(false),										//このアクターが実行状態であるかのフラグ。On,Off関数によって管理する
	m_Parent(0),												//アクターの親の存在を示す。
	m_manager(0),												//このアクターが登録されているアクターファクトリーを確保。これがないと子を生成する時面倒
	m_drawsystem(0),											//このアクターに登録されるSpriteNodeを管理
	m_loader(0),												//アクターのアイコンを持ってくるローダー
	m_x(0),m_y(0)										//メインとなるスプライトの座標
{
	dprintfln("Actor();\n\tthis:%x",this);
}


Actor::~Actor(void)
{
	dprintfln("~Actor();");
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();){
		SAFE_DELETE(*it);
		it=m_collisions.erase(it);
	}
	m_Parent=0;
	m_manager=0;
	m_drawsystem=0;
}


bool Actor::Parent_Exist(){
	return ((m_Parent==0) ? false : true);//3項演算子を用いて親の存在を確認
}

#ifdef COLLISION
	std::vector<Collision*> Actor::Get_Collision(){
		return m_collisions;
	}
	void Actor::Add_Collision(C_OPTION option){
		Collision* tmp_collision=new Collision(this,option,m_drawsystem);
		m_collisions.push_back(tmp_collision);
	}
#endif

void Actor::Collision_update(){
	std::vector<Collision*>::iterator it;
	for(it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->update();
	}
}

bool Actor::Kill(){//派生クラスにkillが定義されない場合この関数が適用され、deleteを行う削除が適用される。基本的にはkill関数は定義される
	return false;
}

void Actor::On(){																//アクターを実行状態に変化させる。その際に必要な初期化も行う
	m_launch_flg=true;
}
void Actor::Off(){																//アクターを非実行状態に変化させる。
	m_launch_flg=false;
}
void Actor::Hit(){
}
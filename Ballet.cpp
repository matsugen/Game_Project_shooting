#include "StdAfx.h"
#include "Bullet.h"
/*弾丸の*/

Bullet::Bullet(void)
{
	dprintfln("Bullet();");
	m_icon=0;
	m_Parent=0;
}

/*子となり得る場合、親を引数にしてm_Parentにセットする。*/
//常に親アクターの影響を受ける場合はupdateに、初期化時のみ親に追随するならinitにそうなるように記述する。
/**/
Bullet::Bullet(Actor* parent)
{
	dprintfln("Bullet(parent:%x);\n\tthis:%x",parent,this);
	m_icon=0;
	m_Parent=parent;											//アクターの親の存在を示す。
}


Bullet::~Bullet(void)
{
	OutputDebugString("~Bullet();\n");
	m_drawsystem->remobe_Sprite(m_icon);
}

void Bullet::update(KeyState* Key,ImageLoader* loader){//更新関数
	if(m_launch_flg){
		Move();
		/*すべての更新が終わった後にm_iconなどの位置を更新する。*/
		m_icon->MoveTo(m_x,m_y);
		Hit();
	}
		Collision_update();
}
void Bullet::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){//アクター初期化関数
	if(Parent_Exist()){//親が存在すれば初期化時にその座標に追随し生成
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	m_launch_flg=false;
	/*アクターが起動するまで表示しないようにしたい。すべてのアクターがそうなのだから、何か関数化できないか？*/
		if(!m_icon){
			m_icon=m_drawsystem->add_Sprite();
		}
		m_icon->init_None();
		/*判定の初期化をもう少し簡単にできないか？*/
		/*判定の設定*/
		if(m_collisions.size()<1){
			C_OPTION tmp_option;
			tmp_option.hit_flg=false;
			tmp_option.effective=false;
			tmp_option.m_x=(12-BULLET_WIDTH)/2;
			tmp_option.m_y=0;
			tmp_option.m_w=BULLET_WIDTH;
			tmp_option.m_h=BULLET_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			Add_Collision(tmp_option);
		}
	}else{
		dprintfln("親アクターが存在しません");
	}
}

void Bullet::Move(){
	if(Parent_Exist()){
		/*Move関数は常に座標の計算のみを行う*/
		m_y-=BULLET_SPEED;
		if(m_y<-BULLET_HEIGHT){
			m_death_flg=true;
		}
	}
}
void Bullet::Hit(){
	bool tmp_bool=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		C_OPTION tmp_option=(*it)->Get_Option();
		tmp_bool|=tmp_option.hit_flg;
	}
	if(tmp_bool){
		m_death_flg=true;
	}
}

bool Bullet::Kill(){
	/*Enemyは死んだ時、deleteされず数値をすべて初期化して再利用する*/
	m_init_flg=false;	
	m_death_flg=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->Reset();
	}
	return true;
}

void Bullet::On(){
	m_launch_flg=true;
	m_icon->init_Image(m_loader,"machine_gun");
	if(Parent_Exist()){
		m_x=m_Parent->Get_X()+14;
		m_y=m_Parent->Get_Y();
	}
	m_icon->MoveTo(m_x,m_y);
	m_icon->Set_ID(GAME_RESOURCE_ID::BULLET);
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->On();
	}
}
void Bullet::Off(){
	m_launch_flg=false;
}
#include "StdAfx.h"
#include "Enemy.h"
#include"Actor.h"


Enemy::Enemy(void)
{
	dprintfln("Enemy();");
	m_icon=0;
	m_Emergency_interval=0;
}


Enemy::~Enemy(void)
{
	dprintfln("~Enemy();");
	m_drawsystem->remobe_Sprite(m_icon);
}

void Enemy::update(KeyState* Key,ImageLoader* loader){						//更新関数:派生クラスのprivateに各種更新をまとめた関数をつくり、それを順に実行する
	if(m_Emergency_interval>0){
		m_Emergency_interval--;
	}else if(m_Emergency_interval==0){
		On();
		m_Emergency_interval=-1;
	}
	if(m_launch_flg){
		m_y+=m_speed;
		m_icon->MoveTo(m_x,m_y);
		if(m_y>480){
		m_death_flg=true;
		}
	}
	Hit();
	Collision_update();
}
void Enemy::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){	//アクター初期化関数
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	/*アクターが起動するまで表示しないようにしたい。すべてのアクターがそうなのだから、何か関数化できないか？*/
	if(!m_icon){
		m_icon=m_drawsystem->add_Sprite();
	}
	m_icon->init_None();
	/*判定の初期化をもう少し簡単にできないか？*/
	/*判定のステータス設定*/
	if(m_collisions.size()<1){
		C_OPTION tmp_option;
		tmp_option.owner=OWNER::ENEMY;
		tmp_option.hit_flg=false;
		tmp_option.effective=false;
		tmp_option.m_x=m_x;
		tmp_option.m_y=m_y;
		tmp_option.m_w=ENEMY_WIDTH;
		tmp_option.m_h=ENEMY_HEIGHT;
		Add_Collision(tmp_option);
	}
	/*起動までの時間を乱数によって決定*/
	m_Emergency_interval=GetRand(CREATE_INTERVAL_MAX-CREATE_INTERVAL_MIN-1)+CREATE_INTERVAL_MIN;
}
void Enemy::Hit(){															//ゲームシーン側で判定が衝突した場合に呼び出される。
	bool all_hit_flg=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		C_OPTION tmp_option=(*it)->Get_Option();
		all_hit_flg|=tmp_option.hit_flg;
	}
	if(all_hit_flg){
		m_death_flg=true;
	}
}

bool Enemy::Kill(){
	/*Enemyは死んだ時、deleteされず数値をすべて初期化して再利用する*/
	m_init_flg=false;	
	m_death_flg=false;
	m_launch_flg=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->Reset();
	}
	return true;
}


void Enemy::On(){
	m_launch_flg=true;
	m_x=GetRand(PLAYABLE_WIDTH-ENEMY_WIDTH);
	m_y=-ENEMY_HEIGHT*2;
	m_speed=double(GetRand((ENEMY_SPEED_MAX-ENEMY_SPEED_MIN-1)*10))/10.0+ENEMY_SPEED_MIN;
	m_icon->init_Image(m_loader,"player",DIRECTION_DOWN);
	m_icon->Image_Magnificant(2,2);
	m_icon->MoveTo(m_x,m_y);
	m_icon->Set_ID(GAME_RESOURCE_ID::ENEMY);
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->On();
	}
}
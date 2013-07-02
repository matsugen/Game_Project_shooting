#include "StdAfx.h"
#include "Misile.h"


Misile::Misile(void){
	dprintfln("Misile();");
	m_icon=0;
	m_Parent=0;
	m_move_time=0;
	m_angle=0;
	m_dbg=0;
}
Misile::Misile(Actor* parent){
	dprintfln("Misile(parent:%x);\n\tthis:%x",parent,this);
	m_icon=0;
	m_Parent=parent;											//アクターの親の存在を示す。
	m_dbg=0;
}
Misile::~Misile(void){
	OutputDebugString("~Misile();\n");
	m_drawsystem->remobe_Sprite(m_icon);
}
	
double Misile::Misile_Speed(){
	double speed;
	speed=m_move_time*(m_move_time-20)/15+MISILE_MAX_SPEED;
	if(speed>MISILE_MAX_SPEED){
		speed=MISILE_MAX_SPEED;
	}else if(speed<0){
		speed=0;
	}
	return speed;
}

void Misile::Move(){		//弾丸の座標移動だけを行う。
	if(Parent_Exist()){
		double speed=Misile_Speed();
		m_x+=speed*sin(m_angle*PI/180);
		m_y-=speed*cos(m_angle*PI/180);
		/*Move関数は常に座標の計算のみを行う*/
		if(m_y<-MISILE_HEIGHT){
			m_death_flg=true;
		}
	}
}
void Misile::update(KeyState* Key,ImageLoader* loader){
	if(m_launch_flg){
		Move();
		/*すべての更新が終わった後にm_iconなどの位置を更新する。*/
		m_icon->MoveTo(m_x,m_y);
		Hit();
		m_move_time++;
	}
		Collision_update();
}
void Misile::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){//アクター初期化関数
	if(Parent_Exist()){//親が存在すれば初期化時にその座標に追随し生成
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	m_launch_flg=false;
	m_move_time=0;
	m_angle=GetRand(MISILE_ANGLE*2)-MISILE_ANGLE;//ミサイルはある程度の角度の誤差で発射される
	/*アクターが起動するまで表示しないようにしたい。すべてのアクターがそうなのだから、何か関数化できないか？*/
		if(!m_icon){
			m_icon=m_drawsystem->add_Sprite();
		}
		if(!m_dbg){
			m_dbg=m_drawsystem->add_Sprite();
		}
		m_icon->init_None();
		m_dbg->init_None();
		/*判定の初期化をもう少し簡単にできないか？*/
		/*判定の設定*/
		if(m_collisions.size()<1){
			C_OPTION tmp_option;
			tmp_option.hit_flg=false;
			tmp_option.effective=false;
			tmp_option.m_x=(11-MISILE_WIDTH)/2;
			tmp_option.m_y=0;
			tmp_option.m_w=MISILE_WIDTH;
			tmp_option.m_h=MISILE_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			Add_Collision(tmp_option);
		}
	}else{
		dprintfln("親アクターが存在しません");
	}
}
void Misile::Hit(){
	bool tmp_bool=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		C_OPTION tmp_option=(*it)->Get_Option();
		tmp_bool|=tmp_option.hit_flg;
	}
	if(tmp_bool){
		m_death_flg=true;
	}
}
bool Misile::Kill(){
	/*Enemyは死んだ時、deleteされず数値をすべて初期化して再利用する*/
	m_init_flg=false;	
	m_death_flg=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->Reset();
	}
	return true;
}
void Misile::On(){
	m_launch_flg=true;
	m_icon->init_Image(m_loader,"misile");
	m_dbg->init_Circle(2);
	if(Parent_Exist()){
		m_x=m_Parent->Get_X()+14.5;
		m_y=m_Parent->Get_Y();
	}
	m_icon->MoveTo(m_x,m_y);
	m_icon->Set_ID(GAME_RESOURCE_ID::BULLET);
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->On();
	}
}
void Misile::Off(){
	m_launch_flg=false;
}
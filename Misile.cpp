#include "StdAfx.h"
#include "Misile.h"


Misile::Misile(void){
	dprintfln("Misile();");
	m_bomb_flg=false;
	m_bomb_time=0;
	m_icon=0;
	m_Parent=0;
	m_move_time=0;
	m_angle=0;
}
Misile::Misile(Actor* parent){
	dprintfln("Misile(parent:%x);\n\tthis:%x",parent,this);
	m_bomb_flg=false;
	m_bomb_time=0;
	m_icon=0;
	m_Parent=parent;											//�A�N�^�[�̐e�̑��݂������B
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

void Misile::Move(){		//�e�ۂ̍��W�ړ��������s���B
	if(Parent_Exist()){
		double speed=Misile_Speed();
		m_x+=speed*sin(m_angle*PI/180);
		m_y-=speed*cos(m_angle*PI/180);
		/*Move�֐��͏�ɍ��W�̌v�Z�݂̂��s��*/
		if(m_y<-MISILE_HEIGHT){
			m_death_flg=true;
		}
	}
}

void Misile::Bomb(){
	int index;
	if(m_bomb_time>BOMB_TIME-BOMB_TIME/10){
		index=9;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*2/11){
		index=8;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*3/11){
		index=0;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*4/11){
		index=1;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*5/11){
		index=2;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*6/11){
		index=3;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*7/11){
		index=4;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*8/11){
		index=5;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*9/11){
		index=6;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*10/11){
		index=7;
	}else if(m_bomb_time>BOMB_TIME-BOMB_TIME*11/11){
		index=7;
		m_death_flg=true;
	}
	m_bomb_time--;
	m_icon->init_Image(m_loader,"bomb",index);
}
void Misile::update(KeyState* Key,ImageLoader* loader){
	if(m_launch_flg){
		if(m_bomb_flg){
			Bomb();
		}else{
			Move();
			/*���ׂĂ̍X�V���I��������m_icon�Ȃǂ̈ʒu���X�V����B*/
		}
		m_icon->MoveTo(m_x,m_y);
		Hit();
		m_move_time++;
	}
		Collision_update();
}
void Misile::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){//�A�N�^�[�������֐�
	if(Parent_Exist()){//�e�����݂���Ώ��������ɂ��̍��W�ɒǐ�������
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	m_launch_flg=false;
	m_move_time=0;
	m_angle=GetRand(MISILE_ANGLE*2)-MISILE_ANGLE;//�~�T�C���͂�����x�̊p�x�̌덷�Ŕ��˂����
	/*�A�N�^�[���N������܂ŕ\�����Ȃ��悤�ɂ������B���ׂẴA�N�^�[�������Ȃ̂�����A�����֐����ł��Ȃ����H*/
		if(!m_icon){
			m_icon=m_drawsystem->add_Sprite();
		}
		m_icon->init_None();
		/*����̏����������������ȒP�ɂł��Ȃ����H*/
		/*����̐ݒ�*/
		if(m_collisions.size()<1){
			C_OPTION tmp_option;
			tmp_option.hit_flg=false;
			tmp_option.effective=false;
			tmp_option.m_x=(22-MISILE_WIDTH)/2;
			tmp_option.m_y=0;
			tmp_option.m_w=MISILE_WIDTH;
			tmp_option.m_h=MISILE_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			Add_Collision(tmp_option);
		}
	}else{
		dprintfln("�e�A�N�^�[�����݂��܂���");
	}
}
void Misile::Hit(){
	bool tmp_bool=false;
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		C_OPTION tmp_option=(*it)->Get_Option();
		tmp_bool|=tmp_option.hit_flg;
	}
	if(tmp_bool&&!m_bomb_flg){
		m_icon->init_Image(m_loader,"bomb",9);
		m_icon->Image_Magnificant(2.0,2.0);
		m_x+=(11-192)/2;
		m_y+=(50-192)/2;
		m_icon->MoveTo(m_x,m_y);
		C_OPTION tmp_option;
			tmp_option.hit_flg=false;
			tmp_option.effective=true;
			tmp_option.m_x=(192-BOMB_WIDTH)/2;
			tmp_option.m_y=(192-BOMB_HEIGHT)/2;
			tmp_option.m_w=BOMB_WIDTH;
			tmp_option.m_h=BOMB_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			m_collisions[0]->Set_Option(tmp_option);
		m_bomb_flg=true;
		m_bomb_time=BOMB_TIME;
	}
}
bool Misile::Kill(){
	/*Enemy�͎��񂾎��Adelete���ꂸ���l�����ׂď��������čė��p����*/
	m_init_flg=false;	
	m_death_flg=false;
	m_bomb_flg=false;
	m_bomb_time=0;
	/*�~�T�C���̔�����~�T�C���̂��̂ɕK���߂�*/
			C_OPTION tmp_option;
			tmp_option.hit_flg=false;
			tmp_option.effective=false;
			tmp_option.m_x=(22-MISILE_WIDTH)/2;
			tmp_option.m_y=0;
			tmp_option.m_w=MISILE_WIDTH;
			tmp_option.m_h=MISILE_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			m_collisions[0]->Set_Option(tmp_option);
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->Reset();
	}
	return true;
}
void Misile::On(){
	m_launch_flg=true;
	m_icon->init_Image(m_loader,"misile");
	m_icon->Image_Magnificant(2.0,2.0);
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
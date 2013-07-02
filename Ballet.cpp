#include "StdAfx.h"
#include "Bullet.h"
/*�e�ۂ�*/

Bullet::Bullet(void)
{
	dprintfln("Bullet();");
	m_icon=0;
	m_Parent=0;
}

/*�q�ƂȂ蓾��ꍇ�A�e�������ɂ���m_Parent�ɃZ�b�g����B*/
//��ɐe�A�N�^�[�̉e�����󂯂�ꍇ��update�ɁA���������̂ݐe�ɒǐ�����Ȃ�init�ɂ����Ȃ�悤�ɋL�q����B
/**/
Bullet::Bullet(Actor* parent)
{
	dprintfln("Bullet(parent:%x);\n\tthis:%x",parent,this);
	m_icon=0;
	m_Parent=parent;											//�A�N�^�[�̐e�̑��݂������B
}


Bullet::~Bullet(void)
{
	OutputDebugString("~Bullet();\n");
	m_drawsystem->remobe_Sprite(m_icon);
}

void Bullet::update(KeyState* Key,ImageLoader* loader){//�X�V�֐�
	if(m_launch_flg){
		Move();
		/*���ׂĂ̍X�V���I��������m_icon�Ȃǂ̈ʒu���X�V����B*/
		m_icon->MoveTo(m_x,m_y);
		Hit();
	}
		Collision_update();
}
void Bullet::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){//�A�N�^�[�������֐�
	if(Parent_Exist()){//�e�����݂���Ώ��������ɂ��̍��W�ɒǐ�������
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	m_launch_flg=false;
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
			tmp_option.m_x=(12-BULLET_WIDTH)/2;
			tmp_option.m_y=0;
			tmp_option.m_w=BULLET_WIDTH;
			tmp_option.m_h=BULLET_HEIGHT;
			tmp_option.owner=OWNER::BULLET;
			Add_Collision(tmp_option);
		}
	}else{
		dprintfln("�e�A�N�^�[�����݂��܂���");
	}
}

void Bullet::Move(){
	if(Parent_Exist()){
		/*Move�֐��͏�ɍ��W�̌v�Z�݂̂��s��*/
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
	/*Enemy�͎��񂾎��Adelete���ꂸ���l�����ׂď��������čė��p����*/
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
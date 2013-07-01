#include "StdAfx.h"
#include "Collision.h"

Collision::Collision(void)
{
	dprintfln("Collision();");
	m_option.m_x=m_option.m_y=m_option.m_w=m_option.m_h=0;
	m_option.hit_flg=false;
	m_option.owner=OWNER::NONE;
	m_owner=0;
#ifndef NDEBUG
	m_drawsystem=0;
	m_box=0;
#endif
}

Collision::Collision(Actor* owner,C_OPTION option,DrawSystem* ds)
{
	dprintfln("Collision(owner:%x);\n\tthis:%x",owner,this);
	m_owner=owner;
	m_option=option;
#ifndef NDEBUG
	int r,g,b;
	m_drawsystem=ds;
	m_box=ds->add_Sprite();
	m_box->init_Box(option.m_w,option.m_h);
	switch(m_option.owner){	
	case OWNER::PLAYER:
		r=255;
		g=0;
		b=0;
		break;
	case OWNER::ENEMY:
		r=0;
		g=0;
		b=255;
		break;
	case OWNER::BULLET:
		r=0;
		g=255;
		b=0;
		break;
	default:
		r=g=b=0;
		break;
	}
	m_box->Change_Color(r,g,b);
	m_box->MoveTo(option.m_x,option.m_y);//ほぼ手前に表示されるように
	m_box->Set_ID(COLLISION_ID);
	m_box->Blend_Setting(DX_BLENDMODE_ALPHA,128);//半透明にする。
#endif
}

Collision::~Collision(void)
{
	dprintfln("~Collision();");
#ifndef NDEBUG
	m_drawsystem->remobe_Sprite(m_box);
	m_box=0;
#endif
}

void Collision::Hit(){
	m_option.hit_flg=true;
}
C_OPTION Collision::Get_Option(){
	return m_option;
}

void Collision::update(){
	if(m_owner==0){
		dprintfln("%x:この判定を所持するアクターが存在しません\n",this);
	}else{
		m_option.m_y=m_owner->Get_Y();
		if(m_option.owner!=OWNER::PLAYER){
			m_option.m_x=m_owner->Get_X();
		}
#ifndef NDEBUG
		if(!m_option.effective){
			m_box->init_None();
		}else{
			m_box->init_Box(m_option.m_w,m_option.m_h);
			m_box->MoveTo(m_option.m_x,m_option.m_y);//ほぼ手前に表示されるように
		}
#endif
	}
}
void Collision::On(){
	m_option.effective=true;
}
void Collision::Reset(){
		m_option.hit_flg=false;
		m_option.effective=false;
}
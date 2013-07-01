#include "StdAfx.h"
#include "TestScene.h"


TestScene::TestScene(void)
{
	SRand(GetNowCount());
	OutputDebugString("TestScene();\n\t");
	m_score=0;
}


TestScene::~TestScene(void)
{
	OutputDebugString("~TestScene();\n");
}

GameScene* TestScene::update(KeyState* Key){
	GameScene* next=this;
	if(m_score->get_point()==0){
		next=0;
	}
	Collision_judge();
	m_manager->init(m_drawsystem,m_loader,m_manager);		//もしシーン内のアクターの更新が終了したあと新たにアクターが生成されていればそれの初期化を行う。
	m_manager->update(Key,m_loader);						//管理されているすべてのアクターを更新
	return next;
}

void TestScene::init(ImageLoader *loader){
	m_loader=loader;
	for(int i=0;i<ENEMYS_MAX;i++){
		m_manager->add_actor(new Enemy());
	}
	m_manager->add_actor(new Player());	//Playerを設定。
	m_score=new Score_Board();
	m_manager->add_actor(m_score);
	m_manager->init(m_drawsystem,m_loader,m_manager);		//開始時に必ず管理されているすべてのアクターを初期化
}

void TestScene::Draw(){
	m_drawsystem->Draw();
}


bool Judge(Collision* collision1,Collision* collision2){
	C_OPTION option1=collision1->Get_Option();
	C_OPTION option2=collision2->Get_Option();
  return
	  ((	option1.m_x				<	option2.m_x+option2.m_w)
    && (option1.m_x+option1.m_w >	option2.m_x)
	&& (option1.m_y				<	option2.m_y+option2.m_h)
    && (option1.m_y+option1.m_h >	option2.m_y));
}

void TestScene::Collision_judge(){
	std::vector<Actor*> tmp_actors;
	std::vector<Collision*> tmp_collisions,p_collision,e_collision,b_collision;
	tmp_actors=m_manager->Get_AllActors();
	for(std::vector<Actor*>::iterator a_it=tmp_actors.begin();a_it!=tmp_actors.end();++a_it){
		tmp_collisions=(*a_it)->Get_Collision();
		for(std::vector<Collision*>::iterator it=tmp_collisions.begin();it!=tmp_collisions.end();++it){
			C_OPTION tmp_option=(*it)->Get_Option();
			if(tmp_option.effective){
				switch(tmp_option.owner){
				case OWNER::PLAYER:
					p_collision.push_back(*it);
					break;
				case OWNER::BULLET:
					b_collision.push_back(*it);
					break;
				case OWNER::ENEMY:
					e_collision.push_back(*it);
					break;
				default:
					break;
				}
			}
		}
	}
	for(std::vector<Collision*>::iterator e_it=e_collision.begin();e_it!=e_collision.end();++e_it){
		for(std::vector<Collision*>::iterator p_it=p_collision.begin();p_it!=p_collision.end();++p_it){
			if(Judge(*e_it,*p_it)){
				(*e_it)->Hit();
				m_score->reduce_point();
			}
		}
		for(std::vector<Collision*>::iterator b_it=b_collision.begin();b_it!=b_collision.end();++b_it){
			if(Judge(*e_it,*b_it)){
				(*e_it)->Hit();
				(*b_it)->Hit();			
				m_score->add_point();
			}
		}
	}
}
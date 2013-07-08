#include "StdAfx.h"
#include "Score_Board.h"


Score_Board::Score_Board(void)
{
	dprintfln("Score_Board();\n\tthis:%x",this);
	m_back=0;
	m_text=0;
	m_point=0;
}


Score_Board::~Score_Board(void)
{
	dprintfln("~Score_Board()");
	m_drawsystem->remobe_Sprite(m_back);
	m_back=0;
	m_drawsystem->remobe_Sprite(m_text);
	m_text=0;
}


void Score_Board::update(KeyState* Key,ImageLoader* loader){//更新関数
	m_text->init_Text("Score:%08d",m_point);
}
void Score_Board::init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager){//アクター初期化関数
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	m_point=10000;
	/*スコアの背景のセット*/
	m_back=m_drawsystem->add_Sprite();
	m_back->init_Box(WINDOW_WIDTH-PLAYABLE_WIDTH,WINDOW_HEIGHT);
	m_back->Change_Color(150,150,150);
	m_back->MoveTo(PLAYABLE_WIDTH,0);
	m_back->Set_ID(FRONT_GROUND_ID);
	/*スコアの文字列のセット*/
	m_text=m_drawsystem->add_Sprite();
	m_text->init_Text("Score:%08d",m_point);
	m_text->Text_Size(18);
	m_text->Change_Color(0,0,0);
	m_text->MoveTo(PLAYABLE_WIDTH+10,10);
	m_text->Set_ID(FRONT_GROUND_ID);
}

void Score_Board::add_point(){
	m_point+=100;
}
void Score_Board::reduce_point(){
	m_point-=100;
	if(m_point<0){
		m_point=0;
	}
}
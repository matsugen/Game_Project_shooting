#include "StdAfx.h"
#include "Player.h"
/*player.pngのどのアイコンを使うかを指定するための方向マクロ*/
Player::Player(void)
{
	dprintfln("Player();\n\tthis:%x",this);
	m_x=(PLAYABLE_WIDTH-PLAYER_WIDTH)/2;						//メインとなるスプライトの座標
	m_y=WINDOW_HEIGHT-PLAYER_HEIGHT;
	m_d=DIRECTION_UP;							//デフォルトは上
	m_walk_time=0;			
	m_attack_num=0;
	m_angle=0;
	m_icon=0;
	m_bullet.reserve(MAX_BULLET);
}


Player::~Player(void)
{
	dprintfln("~Player();");
	m_drawsystem->remobe_Sprite(m_icon);
	for(std::vector<Actor*>::iterator it=m_bullet.begin();it!=m_bullet.end();){
		m_manager->remove_actor(*it);
		it=m_bullet.erase(it);
	}
}

void Player::init(DrawSystem *ds,ImageLoader *loader,ActorManager* manager){
	m_collisions.reserve(1);					//判定の数は一個
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	/*弾の生成*/
	for(int i=0;i<MAX_BULLET;i++){
		m_bullet.push_back(m_manager->add_actor(new Bullet(this)));
	}
	/*m_iconの初期化*/
	m_icon=m_drawsystem->add_Sprite();		//描画システムにSpriteNode*を登録し、そのポインタをm_iconに書き込む。m_iconを使って管理する
	m_icon->init_Image(loader,"player",0);	//ローダーからプレイヤーアイコンを取ってくる
	m_icon->Image_Magnificant(2.0,2.0);		//倍率2倍
	m_icon->Set_ID(GAME_RESOURCE_ID::PLAYER);
	/*判定の設定*/
	if(m_collisions.size()<1){
		C_OPTION tmp_option;
		tmp_option.hit_flg=false;
		tmp_option.m_x=0;
		tmp_option.m_y=m_y;
		tmp_option.m_w=PLAYABLE_WIDTH;
		tmp_option.m_h=PLAYER_HEIGHT;
		tmp_option.owner=OWNER::PLAYER;
		Add_Collision(tmp_option);
	}
}

/*作るゲームが変わったので使わない
int direction(KeyState* Key,double *angle){	//キー入力で方向を決定する関数
	int up_down=0,right_left=0;		//up_downは1で上-1で下。0でナシ　right_leftは1で右-1で左　0でナシ　両方0で下向き
	if(Key->GetKeyState(KEY_INPUT_W)&&!Key->GetKeyState(KEY_INPUT_S)){
		up_down=1;
	}
	if(Key->GetKeyState(KEY_INPUT_S)&&!Key->GetKeyState(KEY_INPUT_W)){
		up_down=-1;
	}
	if((Key->GetKeyState(KEY_INPUT_W)&&Key->GetKeyState(KEY_INPUT_S))|(!Key->GetKeyState(KEY_INPUT_W)&&!Key->GetKeyState(KEY_INPUT_S))){
		up_down=0;
	}
	if(Key->GetKeyState(KEY_INPUT_D)&&!Key->GetKeyState(KEY_INPUT_A)){
		right_left=1;
	}
	if(Key->GetKeyState(KEY_INPUT_A)&&!Key->GetKeyState(KEY_INPUT_D)){
		right_left=-1;
	}
	if((Key->GetKeyState(KEY_INPUT_A)&&Key->GetKeyState(KEY_INPUT_D))||(!Key->GetKeyState(KEY_INPUT_A)&&!Key->GetKeyState(KEY_INPUT_D))){
		right_left=0;
	}
	if(up_down==-1){//下
		if(right_left==0){//左右なし
			*angle=PI*1/2;
			return DIRECTION_DOWN;
		}
		if(right_left==-1){//左
			*angle=PI*3/4;
			return DIRECTION_LEFT_DOWN;
		}
		if(right_left==1){//右
			*angle=PI*1/4;
			return DIRECTION_RIGHT_DOWN;
		}
	}
	if(up_down==0){//上下なし
		if(right_left==0){//左右なし
			*angle=PI*1/2;
			return DIRECTION_DOWN;
		}
		if(right_left==-1){//左
			*angle=PI*1;
			return DIRECTION_LEFT;
		}
		if(right_left==1){//右
			*angle=PI*0;
			return DIRECTION_RIGHT;
		}
	}
	if(up_down==1){//上
		if(right_left==0){//左右なし
			*angle=PI*3/2;
			return DIRECTION_UP;
		}
		if(right_left==-1){//左
			*angle=PI*5/4;
			return DIRECTION_LEFT_UP;
		}
		if(right_left==1){//右
			*angle=PI*7/4;
			return DIRECTION_RIGHT_UP;
		}
	}
}
*/

void Player::update(KeyState *Key,ImageLoader* loader){
		Move(Key);
		Attack(Key);
		m_icon->init_Image(loader,"player",m_d+((m_walk_time/15)%3));
		Collision_update();
}

void Player::Attack(KeyState* Key){
	if(Key->GetKeyDown(KEY_INPUT_RETURN)||Key->GetKeyDown(KEY_INPUT_SPACE)){
		for(std::vector<Actor*>::iterator it=m_bullet.begin();it!=m_bullet.end();++it){
			if(!((*it)->IsDeath()||(*it)->Get_Launch_flg())){
				(*it)->On();
				return;
			}
		}
	}
}

void Player::Move(KeyState* Key){
	/*
	if(Key->GetKeyState(KEY_INPUT_W)){	//上へ
		m_y-=MOVE_SPEED;
	}
	*/
	if(Key->GetKeyState(KEY_INPUT_A)){	//左へ
		m_x-=MOVE_SPEED;
		m_d=DIRECTION_LEFT;
	}
	if(Key->GetKeyState(KEY_INPUT_D)){	//右へ			
		m_x+=MOVE_SPEED;
		m_d=DIRECTION_RIGHT;
	}
	if(!Key->GetKeyState(KEY_INPUT_A)&&!Key->GetKeyState(KEY_INPUT_D)){
		m_d=DIRECTION_UP;
	}
	/*
	if(Key->GetKeyState(KEY_INPUT_S)){	//下へ
		m_y+=MOVE_SPEED;
	}
	*/
	/*ゲーム画面からはみ出さないようにする*/
	if(m_x<0){
		m_x=0;
	}
	/*
	if(m_y<0){
		m_y=0;
	}
	*/
	if(m_x>PLAYABLE_WIDTH-PLAYER_WIDTH){
		m_x=PLAYABLE_WIDTH-PLAYER_WIDTH;
	}
	/*
	if(m_y>WINDOW_HEIGHT-PLAYER_HEIGHT){
		m_y=WINDOW_HEIGHT-PLAYER_HEIGHT;
	}
	*/
	m_icon->MoveTo(m_x,m_y);

}
#include "StdAfx.h"
#include "Player.h"
/*player.png�̂ǂ̃A�C�R�����g�������w�肷�邽�߂̕����}�N��*/
Player::Player(void)
{
	dprintfln("Player();\n\tthis:%x",this);
	m_x=(PLAYABLE_WIDTH-PLAYER_WIDTH)/2;						//���C���ƂȂ�X�v���C�g�̍��W
	m_y=WINDOW_HEIGHT-PLAYER_HEIGHT;
	m_d=DIRECTION_UP;							//�f�t�H���g�͏�
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
	m_collisions.reserve(1);					//����̐��͈��
	m_drawsystem=ds;
	m_manager=manager;
	m_loader=loader;
	/*�e�̐���*/
	for(int i=0;i<MAX_BULLET;i++){
		m_bullet.push_back(m_manager->add_actor(new Bullet(this)));
	}
	/*m_icon�̏�����*/
	m_icon=m_drawsystem->add_Sprite();		//�`��V�X�e����SpriteNode*��o�^���A���̃|�C���^��m_icon�ɏ������ށBm_icon���g���ĊǗ�����
	m_icon->init_Image(loader,"player",0);	//���[�_�[����v���C���[�A�C�R��������Ă���
	m_icon->Image_Magnificant(2.0,2.0);		//�{��2�{
	m_icon->Set_ID(GAME_RESOURCE_ID::PLAYER);
	/*����̐ݒ�*/
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

/*���Q�[�����ς�����̂Ŏg��Ȃ�
int direction(KeyState* Key,double *angle){	//�L�[���͂ŕ��������肷��֐�
	int up_down=0,right_left=0;		//up_down��1�ŏ�-1�ŉ��B0�Ńi�V�@right_left��1�ŉE-1�ō��@0�Ńi�V�@����0�ŉ�����
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
	if(up_down==-1){//��
		if(right_left==0){//���E�Ȃ�
			*angle=PI*1/2;
			return DIRECTION_DOWN;
		}
		if(right_left==-1){//��
			*angle=PI*3/4;
			return DIRECTION_LEFT_DOWN;
		}
		if(right_left==1){//�E
			*angle=PI*1/4;
			return DIRECTION_RIGHT_DOWN;
		}
	}
	if(up_down==0){//�㉺�Ȃ�
		if(right_left==0){//���E�Ȃ�
			*angle=PI*1/2;
			return DIRECTION_DOWN;
		}
		if(right_left==-1){//��
			*angle=PI*1;
			return DIRECTION_LEFT;
		}
		if(right_left==1){//�E
			*angle=PI*0;
			return DIRECTION_RIGHT;
		}
	}
	if(up_down==1){//��
		if(right_left==0){//���E�Ȃ�
			*angle=PI*3/2;
			return DIRECTION_UP;
		}
		if(right_left==-1){//��
			*angle=PI*5/4;
			return DIRECTION_LEFT_UP;
		}
		if(right_left==1){//�E
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
	if(Key->GetKeyState(KEY_INPUT_W)){	//���
		m_y-=MOVE_SPEED;
	}
	*/
	if(Key->GetKeyState(KEY_INPUT_A)){	//����
		m_x-=MOVE_SPEED;
		m_d=DIRECTION_LEFT;
	}
	if(Key->GetKeyState(KEY_INPUT_D)){	//�E��			
		m_x+=MOVE_SPEED;
		m_d=DIRECTION_RIGHT;
	}
	if(!Key->GetKeyState(KEY_INPUT_A)&&!Key->GetKeyState(KEY_INPUT_D)){
		m_d=DIRECTION_UP;
	}
	/*
	if(Key->GetKeyState(KEY_INPUT_S)){	//����
		m_y+=MOVE_SPEED;
	}
	*/
	/*�Q�[����ʂ���͂ݏo���Ȃ��悤�ɂ���*/
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
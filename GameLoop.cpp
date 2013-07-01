#include "StdAfx.h"
#include "GameLoop.h"


GameLoop::GameLoop(void):
	draw_time	(0),
	update_time	(0),
	init_time	(0),
	elasped_time(0)
{
	dprintfln("GameLoop();\n");
	m_StartTime = 0;
	m_Count = 0;
	m_Fps = 0;
	//�Ƃ肠����null(0)�ŏ��������Ă���
	m_Scene=0;
	m_Key=0;
	m_game_quit=false;
	m_loader=new ImageLoader();
}


GameLoop::~GameLoop(void)
{
	draw_time/=(double)elasped_time;
	update_time/=(double)elasped_time;
	dprintfln("~GameLoop();\n\t�o�ߎ���:%dF\n\t����������:%d ms\n\t�X�V����:%lf ms\n\t�`�掞��:%lf ms",elasped_time,init_time,update_time,draw_time);
	SAFE_DELETE(m_Key);
	SAFE_DELETE(m_loader);
	SAFE_DELETE(m_Scene);
}

void GameLoop::init(GameScene::MODE mode){
	init_time=GetNowCount();
	m_Key=new KeyState();							//�L�[�N���X������������
	m_loader->add_divimage("player","player.png",24,6,4,PLAYER_WIDTH/2,PLAYER_HEIGHT/2);	//Player�A�C�R���̃��[�h�B����24(8����*3)�T�C�Y��20*28
	m_loader->add_image("misile","misile.png");
	switch(mode){
	case GameScene::TEST:
		m_Scene=new TestScene();
		m_Scene->init(m_loader);
		break;
	/*���݂��Ȃ��V�[���B���邢��GameScene::NONE�̏ꍇ�̓V�[���𐶐������Am_Scene��null�̂܂�*/
	case GameScene::NONE:
	default:
		break;										
	}
	init_time=GetNowCount()-init_time;
}

void GameLoop::update(){
	int pre_time=GetNowCount();
//#ifndef NDEBUG
	if( m_Count == 0 ){ //1�t���[���ڂȂ玞�����L��
		m_StartTime = GetNowCount();
	}
	if( m_Count == SAMPLE_NUM ){ //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		m_Fps = 1000.f/((t-m_StartTime)/(float)SAMPLE_NUM);
		m_Count = 0;
		m_StartTime = t;
	}
	m_Count++;
//#endif
	GameScene *next=m_Scene;						//�V�[���ɕύX���Ȃ��ꍇ�͍��̃V�[�����g���̂ŁA���̃V�[�������Ă���
	if(m_Key) m_Key->Keyupdate();					//�L�[���̍X�V
	else {
		printf("m_Key not found\n");				//�L�[�N���X�����݂��Ȃ��ꍇ�G���[��f��
		m_game_quit=true;
	}
	if(m_Scene){
		next=m_Scene->update(m_Key);				//�Q�[���V�[���̍X�V
		if(next!=m_Scene){
			/*�V�[�����ω����Ă����ꍇ���̃V�[���������Ď��̃V�[���ŏ㏑������*/
			SAFE_DELETE(m_Scene);
			m_Scene=next;
		}
	}
	if(m_Key->GetKeyState(KEY_INPUT_ESCAPE)) m_game_quit=true;//�G�X�P�[�v�L�[�������ꂽ��Q�[���I��
	update_time+=GetNowCount()-pre_time;
}

void GameLoop::draw(){
	int pre_time=GetNowCount();
	ClearDrawScreen();						
//#ifndef NDEBUG
	DrawFormatString(0, 0, GetColor(0,0,0), "%.1f", m_Fps);
//#endif
	if(m_Scene){		//����ʂ̏�����
		m_Scene->Draw();
	draw_time+=GetNowCount()-pre_time;
		ScreenFlip();//����ʂ̏���\��ʂ�
	}
}

void GameLoop::wait(){
	elasped_time++;
	int tookTime = GetNowCount() - m_StartTime;	//������������
	int waitTime = m_Count*1000/FPS - tookTime;	//�҂ׂ�����
	if( waitTime > 0 ){
		Sleep(waitTime);	//�ҋ@
	}
}
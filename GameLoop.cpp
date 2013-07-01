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
	//とりあえずnull(0)で初期化しておく
	m_Scene=0;
	m_Key=0;
	m_game_quit=false;
	m_loader=new ImageLoader();
}


GameLoop::~GameLoop(void)
{
	draw_time/=(double)elasped_time;
	update_time/=(double)elasped_time;
	dprintfln("~GameLoop();\n\t経過時間:%dF\n\t初期化時間:%d ms\n\t更新時間:%lf ms\n\t描画時間:%lf ms",elasped_time,init_time,update_time,draw_time);
	SAFE_DELETE(m_Key);
	SAFE_DELETE(m_loader);
	SAFE_DELETE(m_Scene);
}

void GameLoop::init(GameScene::MODE mode){
	init_time=GetNowCount();
	m_Key=new KeyState();							//キークラスを初期化する
	m_loader->add_divimage("player","player.png",24,6,4,PLAYER_WIDTH/2,PLAYER_HEIGHT/2);	//Playerアイコンのロード。数は24(8方向*3)サイズは20*28
	m_loader->add_image("misile","misile.png");
	switch(mode){
	case GameScene::TEST:
		m_Scene=new TestScene();
		m_Scene->init(m_loader);
		break;
	/*存在しないシーン。あるいはGameScene::NONEの場合はシーンを生成せず、m_Sceneはnullのまま*/
	case GameScene::NONE:
	default:
		break;										
	}
	init_time=GetNowCount()-init_time;
}

void GameLoop::update(){
	int pre_time=GetNowCount();
//#ifndef NDEBUG
	if( m_Count == 0 ){ //1フレーム目なら時刻を記憶
		m_StartTime = GetNowCount();
	}
	if( m_Count == SAMPLE_NUM ){ //60フレーム目なら平均を計算する
		int t = GetNowCount();
		m_Fps = 1000.f/((t-m_StartTime)/(float)SAMPLE_NUM);
		m_Count = 0;
		m_StartTime = t;
	}
	m_Count++;
//#endif
	GameScene *next=m_Scene;						//シーンに変更がない場合は今のシーンを使うので、今のシーンを入れておく
	if(m_Key) m_Key->Keyupdate();					//キー情報の更新
	else {
		printf("m_Key not found\n");				//キークラスが存在しない場合エラーを吐く
		m_game_quit=true;
	}
	if(m_Scene){
		next=m_Scene->update(m_Key);				//ゲームシーンの更新
		if(next!=m_Scene){
			/*シーンが変化していた場合今のシーンを消して次のシーンで上書きする*/
			SAFE_DELETE(m_Scene);
			m_Scene=next;
		}
	}
	if(m_Key->GetKeyState(KEY_INPUT_ESCAPE)) m_game_quit=true;//エスケープキーが押されたらゲーム終了
	update_time+=GetNowCount()-pre_time;
}

void GameLoop::draw(){
	int pre_time=GetNowCount();
	ClearDrawScreen();						
//#ifndef NDEBUG
	DrawFormatString(0, 0, GetColor(0,0,0), "%.1f", m_Fps);
//#endif
	if(m_Scene){		//裏画面の初期化
		m_Scene->Draw();
	draw_time+=GetNowCount()-pre_time;
		ScreenFlip();//裏画面の情報を表画面へ
	}
}

void GameLoop::wait(){
	elasped_time++;
	int tookTime = GetNowCount() - m_StartTime;	//かかった時間
	int waitTime = m_Count*1000/FPS - tookTime;	//待つべき時間
	if( waitTime > 0 ){
		Sleep(waitTime);	//待機
	}
}
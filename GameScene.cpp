#include "StdAfx.h"
#include "GameScene.h"


GameScene::GameScene(void){
	dprintfln("GameScene();");
	m_drawsystem=new DrawSystem();
	m_manager=new ActorManager();
}


GameScene::~GameScene(void)
{
	dprintfln("~GameScene();");
	SAFE_DELETE(m_manager);
	SAFE_DELETE(m_drawsystem);
}

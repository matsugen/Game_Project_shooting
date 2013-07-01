#include "StdAfx.h"
#include "KeyState.h"


KeyState::KeyState(void)
{
	dprintfln("KeyState();");
	//キーデータをすべて初期化
	for(int i=0;i<KEYNUM;i++){
		PreKey[i]=0;
		Key[i]=0;
		KeyDown[i]=false;
		KeyUp[i]=false;
	}
}


KeyState::~KeyState(void)
{
	dprintfln("~KeyState();");
}

void KeyState::Keyupdate(){
	if(GetHitKeyStateAll(Key)==-1){//現在のキー状態を取得
		dprintfln("キー状態の取得に失敗しました");
	}else{
		for(int i=0;i<KEYNUM;i++){
			KeyDown[i]=(Key[i]==1)&&(PreKey[i]==0);
			KeyUp[i]=(Key[i]==0)&&(PreKey[i]==1);
			PreKey[i]=Key[i];
		}
	}
}
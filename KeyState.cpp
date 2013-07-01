#include "StdAfx.h"
#include "KeyState.h"


KeyState::KeyState(void)
{
	dprintfln("KeyState();");
	//�L�[�f�[�^�����ׂď�����
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
	if(GetHitKeyStateAll(Key)==-1){//���݂̃L�[��Ԃ��擾
		dprintfln("�L�[��Ԃ̎擾�Ɏ��s���܂���");
	}else{
		for(int i=0;i<KEYNUM;i++){
			KeyDown[i]=(Key[i]==1)&&(PreKey[i]==0);
			KeyUp[i]=(Key[i]==0)&&(PreKey[i]==1);
			PreKey[i]=Key[i];
		}
	}
}
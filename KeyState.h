#pragma once
#include"stdafx.h"
/*�L�[���͂Ɋւ���N���X*/
class KeyState
{
private:
	char PreKey[KEYNUM];	//���O�ɃL�[��������Ă������ǂ����B������Ă����1�A������Ă��Ȃ����0
	char Key[KEYNUM];		//�L�[��������Ă��邩�ǂ����B������Ă����1�A������Ă��Ȃ����0
	bool KeyDown[KEYNUM];	//�L�[�������ꂽ�u�ԂȂ�true�A����ȊO��false
	bool KeyUp[KEYNUM];		//�L�[�������ꂽ�u�ԂȂ�true�A����ȊO��false
public:
	KeyState(void);
	~KeyState(void);
	void Keyupdate();									//�L�[���̓f�[�^���X�V����
	bool GetKeyState(int index){return (Key[index]==1);}//�w�肵���L�[��������Ă��邩�ǂ������m�F����C�����C���֐�
	bool GetKeyDown(int index){return KeyDown[index];}	//�w�肵���L�[�������ꂽ�u�Ԃ��ǂ������m�F����C�����C���֐�
	bool GetKeyUp(int index){return KeyUp[index];}		//�w�肵���L�[�������ꂽ�u�Ԃ��ǂ������m�F����C�����C���֐�	
};
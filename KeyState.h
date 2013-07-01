#pragma once
#include"stdafx.h"
/*キー入力に関するクラス*/
class KeyState
{
private:
	char PreKey[KEYNUM];	//直前にキーが押されていたかどうか。押されていれば1、押されていなければ0
	char Key[KEYNUM];		//キーが押されているかどうか。押されていれば1、押されていなければ0
	bool KeyDown[KEYNUM];	//キーが押された瞬間ならtrue、それ以外はfalse
	bool KeyUp[KEYNUM];		//キーが離された瞬間ならtrue、それ以外はfalse
public:
	KeyState(void);
	~KeyState(void);
	void Keyupdate();									//キー入力データを更新する
	bool GetKeyState(int index){return (Key[index]==1);}//指定したキーが押されているかどうかを確認するインライン関数
	bool GetKeyDown(int index){return KeyDown[index];}	//指定したキーが押された瞬間かどうかを確認するインライン関数
	bool GetKeyUp(int index){return KeyUp[index];}		//指定したキーが離された瞬間かどうかを確認するインライン関数	
};
/*ゲームの基礎部分に設定するリソース*/
#pragma once

/*すべてのゲームに使える定義*/
#define SAFE_DELETE(x) if(x){delete x;x=0;}
#define SAMPLE_NUM 60
#define KEYNUM 256			//DXライブラリで用いるキーを格納するキーの数
#define FPS 60				//ゲームのfps(frame per second)の値
#define BACKGROUND_R 0xff	//初期化した画面の背景色の赤
#define BACKGROUND_G 0xff	//同上緑
#define BACKGROUND_B 0xff	//同上青
#define WINDOW_WIDTH 640	//ゲーム画面の横解像度
#define WINDOW_HEIGHT 480	//ゲーム画面のタテ解像度
#define COLOR_BIT 16		//ゲームのビット数
#define PI	3.1415926535897932384626433832795f//円周率
#define NUMBER_MAX 8	//添字に使える数字の最大桁数
#define STRING_MAX 256	//文字数の最大数

#define BACK_GROUND_ID -1
#define FRONT_GROUND_ID 0
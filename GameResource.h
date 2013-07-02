
#pragma once
/*コンパイル時つかう定義*/
#define COLLISION //COLLISIONが定義されたらActorのGet_Collision,Set_Collisionが使えるようになる。
#define COLLISION_ID 256
/*ゲームシーンのリソース*/
#define PLAYABLE_WIDTH 400		//Playerが動ける左右の幅
namespace GAME_RESOURCE_ID{
	enum DESCRIPTION_ID{
		BULLET=1,
		ENEMY,
		PLAYER
	};
}

#define MOVE_SPEED 4	//プレイヤーアクターの移動速度
/*Playerアクターの向いている方向*/
#define DIRECTION_DOWN 0		//下向き
#define DIRECTION_LEFT_DOWN 3	//左下向き
#define DIRECTION_LEFT 6		//左向き
#define DIRECTION_RIGHT_DOWN 9	//右下向き
#define DIRECTION_RIGHT 12		//右向き
#define DIRECTION_LEFT_UP 15	//左上向き
#define DIRECTION_UP 18			//上向き
#define DIRECTION_RIGHT_UP 21	//右上向き
#define PLAYER_WIDTH 40			//プレイヤーアイコンの横幅
#define PLAYER_HEIGHT 56		//プレイヤーアイコンのの縦幅

/*弾丸のステータス*/
#define MAX_BULLET 7			//1画面上で存在できる弾の数
#define BULLET_WIDTH 1.0f		//弾丸の横幅
#define BULLET_HEIGHT 30	//弾丸の縦幅
#define BULLET_SPEED 5.5f		//弾丸の速度
/*ミサイルのステータス*/
#define MAX_MISILE 1			//1画面上で存在できる弾の数
#define MISILE_WIDTH 11.0f		//弾丸の横幅
#define MISILE_HEIGHT 50.0f		//弾丸の縦幅
#define MISILE_MAX_SPEED 7.0f	//弾丸の速度

/*EnemyActorのステータス*/
#define ENEMY_SPEED_MAX 3.0f		//敵の移動速度最大値
#define ENEMY_SPEED_MIN 2.0f		//敵の移動速度最小値
#define ENEMY_WIDTH 40		//敵アイコンの横幅
#define ENEMY_HEIGHT 56		//敵アイコンのの縦幅
#define ENEMYS_MAX 10		//1画面上に存在できる敵の最大数
#define CREATE_INTERVAL_MAX 200//敵を生成する間隔(単位はフレーム)
#define CREATE_INTERVAL_MIN 100
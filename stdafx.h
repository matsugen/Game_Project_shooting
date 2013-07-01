// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once
//#define NDEBUG//デバッグモードじゃないときに使う。デバッグ中はコメントアウト
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
/*このプロジェクト以外でも使うヘッダ(<>で括れるもの)*/
#include<string.h>
#include<DxLib.h>
#include<math.h>
#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>
#include<boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include<vector>
/*このプロジェクトでのみ使うヘッダ(""で括るべきもの)*/
/*デバッグ用ヘッダ*/
#include"UsrDebug.h"
/*個人で作るリソースヘッダ*/
#include"MainResource.h"
/*一つのタイトルに限ったヘッダ*/
#include"GameResource.h"
#include"Collision.h"
/*ゲームの土台部分*/
#include"KeyState.h"
#include"GameLoop.h"
#include"SpriteNode.h"
#include"ImageLoader.h"
#include"DrawSystem.h"
#include"Actor.h"
#include"ActorManager.h"
#include"GameScene.h"
/*一つのタイトルに限ったヘッダ*/
#include"TestScene.h"
#include"Player.h"
#include"Bullet.h"
#include"Score_Board.h"
#include"Enemy.h"
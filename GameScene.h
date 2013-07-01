#pragma once
#include"stdafx.h"
#include "GameScene.h"
#include"DrawSystem.h"
#include"KeyState.h"
#include"SpriteNode.h"
#include"Actor.h"
#include"ActorManager.h"
#include"ImageLoader.h"
/*ゲームに使用するシーンの基礎となるクラス。これを派生して使う。*/
class GameScene
{
protected:
	DrawSystem* m_drawsystem;		//描画システム。GameSceneで生成する。
	ImageLoader* m_loader;			//ImageLoaderから画像をとってくる。これはGameLoopから持ってくる
	ActorManager* m_manager;		//アクターを管理するファクトリ。GameSceneで生成する。
public:
	/*ゲームのモードを列挙型で作ってデバッグなどで確認できるようにする*/
	enum MODE{
		NONE,
		TEST
	};
	GameScene(void);
	virtual ~GameScene(void);
	virtual GameScene* update(KeyState* Key)=0;							//フレームごとに呼び出されるシーンを更新する関数
	virtual void Draw()=0;												//フレームごとに呼び出される描画関数
	virtual void init(ImageLoader* loader)=0;							//初期化純粋仮想関数
};


#pragma once
#include"stdafx.h"
/*
TODO:
*/
/*シーンの中にあるアクターを管理するクラス*/
/*
	Actorの派生クラスを生成・保管するため、当然削除もこのクラスが担う。
*/
class Actor;
#include"Actor.h"
class ActorManager
{
private:
	std::vector<Actor*> m_Actor;											//管理するアクターを保管するベクター
	int m_count;															//アクターの数
public:
	ActorManager(void);
	~ActorManager(void);
	void update(KeyState* Key,ImageLoader* loader);							//管理されているすべてのアクターの更新を実行する。nullになったアクターは削除する
	void init(DrawSystem* ds,ImageLoader* loader,ActorManager* manager);	//管理されているすべてのアクターの初期化を行う
	Actor* add_actor(Actor* actor);											//アクターをファクトリに追加する。関数内でインスタンス化し、そのポインタをScene側に管理させるためポインタを返す
	void remove_actor(Actor* actor);										//指定したアクターを削除する。基本的にはActor::m_death_flgを使って削除されるが、デストラクタなどではこちらを使う
	std::vector<Actor*> Get_AllActors();									//すべてのアクターを取得。vectorの形で
};
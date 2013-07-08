#include "StdAfx.h"
#include "ActorManager.h"

ActorManager::ActorManager(void)
{
	dprintfln("ActorManager();");
	m_count=0;
	m_Actor.reserve(512);
}


ActorManager::~ActorManager(void)
{
	dprintfln("~ActorManager();");
	std::vector<Actor*>::iterator it;
	for(it=m_Actor.begin();it!=m_Actor.end();){
		SAFE_DELETE(*it);
		it=m_Actor.erase(it);
	}
}

void ActorManager::update(KeyState* Key,ImageLoader* loader){	//管理されているすべてのアクターの更新を実行する。死状態になったらアクターは削除する
	std::vector<Actor*>::iterator it ;
	for(it=m_Actor.begin();it != m_Actor.end();){
			if((*it)->Initialized()){
				(*it)->update(Key, loader); // 削除されていなければアクターの更新を
			}
			if ((*it)->IsDeath()){	// 死状態がtrueならそのアクターを削除
				if(!(*it)->Kill()){	// 派生クラスにKill関数が定義されていなければ(Actorクラスでただfalseを返す関数を作る)アクターを削除してベクターからも削除する
					SAFE_DELETE(*it);
					it = m_Actor.erase(it); // 要素の削除。erase関数は削除したイテレータの次のイテレータを返すので++itの役割にちかいことをする
				}
			}
			++it;
	}
}

void ActorManager::init(DrawSystem* ds,ImageLoader* loader,ActorManager* manager){
	std::vector<Actor*>::iterator it;
	for(it=m_Actor.begin();it!=m_Actor.end();++it){
		if(!(*it)->Initialized()){				//アクターが初期化済みでなければ初期化し、初期化済みのマークをする
			(*it)->init(ds,loader,manager);		//すべてのアクターを初期化
			(*it)->Ended_init();				//初期化が終了した場合以後初期化しない
		}
	}
}
Actor* ActorManager::add_actor(Actor* actor=0){					//アクターをファクトリに追加する
	dprintfln("%x",actor);
	if(!actor){
		dprintfln("追加するためのアクターが存在しません");
		return 0;
	}
	m_Actor.push_back(actor);
	m_count++;
	return actor;
}

void ActorManager::remove_actor(Actor *actor){
	std::vector<Actor*>::iterator it;
	for(it=m_Actor.begin();it!=m_Actor.end();){//指定したものと同じSpriteが確認されたらSpriteNodeをSAFE_DELETEし、vectorから削除する。
		if(*it==actor){
			SAFE_DELETE(*it);
			it=m_Actor.erase(it);
			return;
		}else{
			++it;
		}
	}
	dprintfln("指定したアクターは存在しません");
}

std::vector<Actor*> ActorManager::Get_AllActors(){
	return m_Actor;
}
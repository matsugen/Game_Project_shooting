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

void ActorManager::update(KeyState* Key,ImageLoader* loader){	//�Ǘ�����Ă��邷�ׂẴA�N�^�[�̍X�V�����s����B����ԂɂȂ�����A�N�^�[�͍폜����
	std::vector<Actor*>::iterator it ;
	for(it=m_Actor.begin();it != m_Actor.end();){
			if((*it)->Initialized()){
				(*it)->update(Key, loader); // �폜����Ă��Ȃ���΃A�N�^�[�̍X�V��
			}
			if ((*it)->IsDeath()){	// ����Ԃ�true�Ȃ炻�̃A�N�^�[���폜
				if(!(*it)->Kill()){	// �h���N���X��Kill�֐�����`����Ă��Ȃ����(Actor�N���X�ł���false��Ԃ��֐������)�A�N�^�[���폜���ăx�N�^�[������폜����
					SAFE_DELETE(*it);
					it = m_Actor.erase(it); // �v�f�̍폜�Berase�֐��͍폜�����C�e���[�^�̎��̃C�e���[�^��Ԃ��̂�++it�̖����ɂ��������Ƃ�����
				}
			}
			++it;
	}
}

void ActorManager::init(DrawSystem* ds,ImageLoader* loader,ActorManager* manager){
	std::vector<Actor*>::iterator it;
	for(it=m_Actor.begin();it!=m_Actor.end();++it){
		if(!(*it)->Initialized()){				//�A�N�^�[���������ς݂łȂ���Ώ��������A�������ς݂̃}�[�N������
			(*it)->init(ds,loader,manager);		//���ׂẴA�N�^�[��������
			(*it)->Ended_init();				//���������I�������ꍇ�Ȍ㏉�������Ȃ�
		}
	}
}
Actor* ActorManager::add_actor(Actor* actor=0){					//�A�N�^�[���t�@�N�g���ɒǉ�����
	dprintfln("%x",actor);
	if(!actor){
		dprintfln("�ǉ����邽�߂̃A�N�^�[�����݂��܂���");
		return 0;
	}
	m_Actor.push_back(actor);
	m_count++;
	return actor;
}

void ActorManager::remove_actor(Actor *actor){
	std::vector<Actor*>::iterator it;
	for(it=m_Actor.begin();it!=m_Actor.end();){//�w�肵�����̂Ɠ���Sprite���m�F���ꂽ��SpriteNode��SAFE_DELETE���Avector����폜����B
		if(*it==actor){
			SAFE_DELETE(*it);
			it=m_Actor.erase(it);
			return;
		}else{
			++it;
		}
	}
	dprintfln("�w�肵���A�N�^�[�͑��݂��܂���");
}

std::vector<Actor*> ActorManager::Get_AllActors(){
	return m_Actor;
}
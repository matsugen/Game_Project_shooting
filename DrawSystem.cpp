#include "StdAfx.h"
#include "DrawSystem.h"
#include<stdio.h>
#include<algorithm>
void Node_Sort(std::vector<SpriteNode*> &v){//�e�q�֌W������Ȃ��悤�ɑ}���\�[�g�A����
	int i,j;
	SpriteNode* key;
	for(j=1 ; j<(signed)v.size() ; j++){
		key = v[j];
		i=j-1;
		while(i>=0 && v[i]->Get_ID() > key->Get_ID()){
			v[i+1]=v[i];
			i--;
		}
		v[i+1] = key;
	}


}

DrawSystem::DrawSystem(void)
{
	dprintfln("DrawSystem();");
	m_Sprite.reserve(8192);
}


DrawSystem::~DrawSystem(void)
{
	dprintfln("~DrawSystem();");
	std::vector<SpriteNode*>::iterator it=m_Sprite.begin();
	for(it=m_Sprite.begin();it!=m_Sprite.end();){
		SAFE_DELETE(*it);
		it=m_Sprite.erase(it);
	}
}

void DrawSystem::Draw(){
	std::vector<SpriteNode*>::iterator it;	//�X�v���C�g�̃C�e���[�^���`
	std::vector<SpriteNode*> b_sprite,f_sprite,chara_sprite;						//�X�v���C�g�f�[�^�̏��Ԃ��Ԉ���ď��������Ȃ��悤�Ƀ��[�J���ϐ����`
#ifdef COLLISION
	std::vector<SpriteNode*> collision_sprite;
#endif
	for(it=m_Sprite.begin();it!=m_Sprite.end();it++){
		/*�\�[�g���Ԃ�Z�����邽�߂ɕ`�悵�Ȃ����̈ȊO�����ꂼ���vector�Ɋi�[���A0<id<256�̂��̂���ID���Ƀ\�[�g����*/
		SpriteNode::TYPE type=(*it)->Get_Type();
		int id=(*it)->Get_ID();
		if(type!=SpriteNode::NONE){
			if(id==BACK_GROUND_ID){
				b_sprite.push_back(*it);
			}else if(id==FRONT_GROUND_ID){
				f_sprite.push_back(*it);
			}else if(0<id&&id<256){
				chara_sprite.push_back(*it);
			}
#ifdef COLLISION
			else if(id==COLLISION_ID){
				collision_sprite.push_back(*it);
			}
#endif
		}
	}
	Node_Sort(chara_sprite);
	for(it=b_sprite.begin();it!=b_sprite.end();it++){
		(*it)->DrawThis();
	}
	for(it=chara_sprite.begin();it!=chara_sprite.end();it++){
		(*it)->DrawThis();
	}
#ifdef COLLISION
	for(it=collision_sprite.begin();it!=collision_sprite.end();it++){
		(*it)->DrawThis();
	}
#endif
	for(it=f_sprite.begin();it!=f_sprite.end();it++){
		(*it)->DrawThis();
	}
}


SpriteNode* DrawSystem::add_Sprite(){
	SpriteNode *sprite=new SpriteNode();
	m_Sprite.push_back(sprite);		//�X�v���C�g�𖖔��ɒǉ�
	return sprite;
}

void DrawSystem::remobe_Sprite(SpriteNode* sprite){
	std::vector<SpriteNode*>::iterator it;
	if(sprite==0){
		dprintfln("�w�肵���X�v���C�g�͑��݂��܂���");
	}else{
		for(it=m_Sprite.begin();it!=m_Sprite.end();){//�w�肵�����̂Ɠ���Sprite���m�F���ꂽ��SpriteNode��SAFE_DELETE���Avector����폜����B
			if(*it==sprite){
				SAFE_DELETE(*it);
				it=m_Sprite.erase(it);
				return;
			}else{
				++it;
			}
		}
	}
}
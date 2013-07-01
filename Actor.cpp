#include "stdafx.h"
#include "Actor.h"


Actor::Actor(void):
	m_death_flg(false),											//�A�N�^�[�̎����
	m_init_flg(false),											//���̃A�N�^�[���������ς݂��ǂ����̃t���O�BActorManager�ɂď���������Ă��Ȃ���Ώ��������s��
	m_launch_flg(false),										//���̃A�N�^�[�����s��Ԃł��邩�̃t���O�BOn,Off�֐��ɂ���ĊǗ�����
	m_Parent(0),												//�A�N�^�[�̐e�̑��݂������B
	m_manager(0),												//���̃A�N�^�[���o�^����Ă���A�N�^�[�t�@�N�g���[���m�ہB���ꂪ�Ȃ��Ǝq�𐶐����鎞�ʓ|
	m_drawsystem(0),											//���̃A�N�^�[�ɓo�^�����SpriteNode���Ǘ�
	m_loader(0),												//�A�N�^�[�̃A�C�R���������Ă��郍�[�_�[
	m_x(0),m_y(0)										//���C���ƂȂ�X�v���C�g�̍��W
{
	dprintfln("Actor();\n\tthis:%x",this);
}


Actor::~Actor(void)
{
	dprintfln("~Actor();");
	for(std::vector<Collision*>::iterator it=m_collisions.begin();it!=m_collisions.end();){
		SAFE_DELETE(*it);
		it=m_collisions.erase(it);
	}
	m_Parent=0;
	m_manager=0;
	m_drawsystem=0;
}


bool Actor::Parent_Exist(){
	return ((m_Parent==0) ? false : true);//3�����Z�q��p���Đe�̑��݂��m�F
}

#ifdef COLLISION
	std::vector<Collision*> Actor::Get_Collision(){
		return m_collisions;
	}
	void Actor::Add_Collision(C_OPTION option){
		Collision* tmp_collision=new Collision(this,option,m_drawsystem);
		m_collisions.push_back(tmp_collision);
	}
#endif

void Actor::Collision_update(){
	std::vector<Collision*>::iterator it;
	for(it=m_collisions.begin();it!=m_collisions.end();++it){
		(*it)->update();
	}
}

bool Actor::Kill(){//�h���N���X��kill����`����Ȃ��ꍇ���̊֐����K�p����Adelete���s���폜���K�p�����B��{�I�ɂ�kill�֐��͒�`�����
	return false;
}

void Actor::On(){																//�A�N�^�[�����s��Ԃɕω�������B���̍ۂɕK�v�ȏ��������s��
	m_launch_flg=true;
}
void Actor::Off(){																//�A�N�^�[�����s��Ԃɕω�������B
	m_launch_flg=false;
}
void Actor::Hit(){
}
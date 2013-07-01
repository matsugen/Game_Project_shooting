#pragma once
#include"stdafx.h"
#include"SpriteNode.h"
/*�`��V�X�e���N���X
	���S��2D�`��p�B��O�����������肷�邽�߂�z���W��p���Ă��邪�A���ߊ���\�����Ă��Ȃ��B
	�܂��ASpriteNode�𐶐��E�ۊǂ��镔���ł���̂œ��R������ō폜���s���B
	MoveTo�ȂǂƂ����������Actor���ɂ����邽�߁ASprite��ǉ�������|�C���^��Ԃ��B
*/
class DrawSystem
{
private:
	/*	SpriteNode���x�N�^�[�Ŋi�[���A�`�悷��Ƃ���z���W�Ń}�[�W�\�[�g���ĕ\���B
		���ݕs��L��BActor��SpriteNode�Ƃ̌��ˍ����ɒ��ӁB
	*/
	std::vector<SpriteNode*> m_Sprite;
public:
	DrawSystem(void);
	~DrawSystem(void);
	/*	�o�^���ꂽSpriteNode��`�悷��B���̎��ASpriteNode��z���W�Ń}�[�W�\�[�g����
		�\�[�g�͏����ŁAz���W���傫�����̂قǉ��ɕ`�悳���B
	*/
	void Draw();							//���ׂẴX�v���C�g��`��B�`�悷��ہA
	/*	SpriteNode��o�^����
	TODO:
		�ȑO��Actor����SpriteNode�����̂܂ܓo�^���Ă������AActor����SpriteNode��delete���Ă�������ɓo�^���Ă���SpriteNode����肭�폜����Ȃ��̂ŁA
		add_Sprite(new SpriteNode())�Ƃ��ēo�^����B
		���̏ꍇ�ASpriteNode�̏��������ǂ����邩�AActor���łǂ������SpriteNode�𑀍삷�邩�Ƃ����ۑ肪������B
	*/
	SpriteNode* add_Sprite();				//�X�v���C�g��ǉ��AActor�ɑ��삳���邽�߂Ƀ|�C���^��Ԃ��B
	void remobe_Sprite(SpriteNode* sprite);	//�����Ɠ����X�v���C�g���폜�B�폜�������͓̂�����SAFE_DELETE����B
};


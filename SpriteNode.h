#pragma once
#include"stdafx.h"
#include"ImageLoader.h"
#include<stdarg.h>
#define DEFAULT_FONTSIZE 12	//�f�t�H���g�̃t�H���g�T�C�Y
//#define CHILDREN_MAX 16		//��̃X�v���C�g�m�[�h���ۗL�ł���q�X�v���C�g�̍ő��
/*�X�v���C�g��̃f�[�^�N���X�BDrawSystem�N���X��vector�Ŋi�[��ID���ɕ`�悷��*/
class SpriteNode
{
public:
	enum TYPE{
		NONE,
		IMAGE,	//�摜
		TEXT,	//����
		LINE,	//����
		BOX,	//��`
		CIRCLE,	//�~
		PIXEL
	};
private:
	/*���͐e�q�֌W�����Ȃ��B�ʓ|�����ǂ��ׂẴX�v���C�g���Ǘ�����
	double children_count;							//�q�X�v���C�g�̐�
	SpriteNode *Parent,*Children[CHILDREN_MAX];	//�X�v���C�g�̐e�Ǝq�̃|�C���^
	*/
	double m_x,m_y;							//�X�v���C�g�̍��W(�摜�Ɖ~�̏ꍇ�͉摜�̒��S�_�A�_�͓_���̂��́B����ȊO�͍���̍��W)
	int m_ID;								//�X�v���C�g�̕`�揇��\��ID(��{,�傫�����̂قǎ�O�ɕ\��)
	TYPE m_type;								//�X�v���C�g�̃^�C�v
	int m_color_r,m_color_g,m_color_b;			//�F�@�摜�ȊO�Ɏg�p
	bool m_fill;								//�h��Ԃ����ǂ����@��`�Ɖ~�Ɏg�p
	int m_Blend_Mode,m_Blend_Pal;				//�u�����h���[�h�ƃp�����[�^(0~255)
	/*�摜�X�v���C�g�Ɏg�������o�ϐ�*/
	int m_image_handler;						//�C���[�W�n���h��
	double m_magni_w,m_magni_h;					//�X�v���C�g�̊g�嗦�B�摜�X�v���C�g�ɂ̂ݓK�p
	bool m_turn,m_trans;						//�X�v���C�g�̍��E���](m_trans)�Ɠ��ߏ���(m_trans)�̗L��
	double m_cx,m_cy;								//�摜����]�����钆�S�_�̍��W
	double m_rad;								//�摜�̉�]�p(rad)

	/*�����X�v���C�g�Ɏg�������o�ϐ�*/
	char m_text[STRING_MAX];
	char m_fontname[STRING_MAX];				//�t�H���g��
	int m_fontsize;								//�t�H���g�T�C�Y

	/*�����E��`�X�v���C�g�Ɏg�������o�ϐ�*/
	double m_w,m_h;								//���ƍ���

	/*�~�̃X�v���C�g�Ɏg�������o�ϐ�*/
	double m_radius;								//�~�̔��a
public:
	SpriteNode(void);
	~SpriteNode(void);
	/*�X�v���C�g�̐e�q�֌W�֐�*/
	/*���͐e�q�֌W�����Ȃ��B�ʓ|�����ǂ��ׂẴX�v���C�g���Ǘ�����
	void Set_Parent(SpriteNode *parent);
	void add_Child(SpriteNode *child);			//�q�X�v���C�g�̒ǉ��B
	void remove_Child(SpriteNode *child);		//�q�X�v���C�g�̍폜�B�q���폜���ꂽ�ꍇ���̎q��艺�ʑw�̃X�v���C�g���폜
	void Get_Children(SpriteNode *children[]);	//���ׂĂ̎q�X�v���C�g���擾����
	*/
	/*���擾�֐�*/
	double Get_X(){return m_x;}										//X���W�̎擾
	double Get_Y(){return m_y;}										//Y���W�̎擾
	int Get_ID(){return m_ID;}										//Z���W�̎擾
	double Get_W();													//��`���̎擾
	double Get_H();													//��`�����̎擾
	double Get_Center_X();											//���SX���W�̎擾
	double Get_Center_Y();											//���SY���W�̎擾
	double Get_Radius();											//���a�̎擾
	SpriteNode::TYPE Get_Type(){return m_type;}

	void MoveTo(double x,double y);
	void Set_ID(int id);
	void Change_Color(int r,int g,int b);							//�F�ݒ�B������s��Ȃ��ꍇ��(0,0,0)
	void Blend_Setting(int mode,int pal);							//�u�����h���[�h�̃Z�b�g�ƃp�����[�^�̐ݒ�B������s��Ȃ��ꍇ�̓u�����h���[�h�͖���
	/*�摜�X�v���C�g�Ɏg�������o�֐�*/
	void init_Image(ImageLoader* loader,char* item_name);			//�A�C�e�����Ń��[�_�[����摜������Ă���B
	void init_Image(ImageLoader* loader,char* item_name,int index);	//�A�C�e�����ƃC���f�b�N�X(0�X�^�[�g)�Ń��[�_�[���炪����������Ă���(add_divimage�œo�^�����^�C�v�̉摜)
	void Image_Rotate(double rad);									//�摜�̉�]�p(rad)��ݒ�B������s��Ȃ��ꍇ�͉�]���Ȃ�
	void Image_Magnificant(double w,double h);						//���ƃ^�e�̊g�嗦�ݒ�B������s��Ȃ��ꍇ�͓��{
	void Image_Reverse();											//���݂̏�Ԃ���摜�𔽓]�B������s��Ȃ��ꍇ�͔��]���Ȃ�
	void Image_Trans(bool flg);										//���ߏ������s�����ǂ�����ݒ�B������s��Ȃ��ꍇ�͓��ߏ������s��
	void Image_Spin_Center(double cx,double cy);							//�摜����]�����钆�S�_�B������s��Ȃ��ꍇ�͒��S�_�͉摜�̍���[
	/*�����X�v���C�g�Ɏg�������o�֐�*/
	void init_Text(const char* text,...);										//��������Z�b�g
	void Text_Font(char *fontname);									//�t�H���g�ݒ�
	void Text_Size(int size);										//�����T�C�Y�̐ݒ�
	/*�����E��`�X�v���C�g�Ɏg�������o�֐�*/
	void init_Line(double x,double y);									//(0,0)����̏I�[���W�Œ������Z�b�g
	void init_Box(double w,double h);										//���ƍ�����ݒ肵�ċ�`���Z�b�g
	void Box_Fill(bool flg);										//��`��h��Ԃ����ۂ�
	/*�~�X�v���C�g�Ɏg�����o�֐�*/
	void init_Circle(double r);										//�~�̔��a��ݒ�
	void Circle_Fill(bool flg);										//�~��h��Ԃ����ۂ�
	/*�_�X�v���C�g�Ɏg�������o�֐�*/
	void init_Pixel();												//�_�X�v���C�g�Ƃ��Đݒ�
	/*�\������Ȃ��X�v���C�g�Ɏg�������o�֐�*/						
	void init_None();												//�\���������Ȃ��X�v���C�g�Ɏg��
	/*�`��Ɏg���֐�*/
	void DrawThis();												//���̃X�v���C�g��`�悷��
};
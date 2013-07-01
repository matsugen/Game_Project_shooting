#include "StdAfx.h"
#include "SpriteNode.h"


SpriteNode::SpriteNode(void)
{
	dprintfln("SpriteNode();");
	m_x=m_y=m_ID=0;								//���W�͂ЂƂ܂�(0,0,0)��
	m_type=NONE;								//���������X�v���C�g�Ƃ��Đݒ�
	m_color_r=m_color_g=m_color_b=0;			//�f�t�H���g�͍�
	m_Blend_Mode=DX_BLENDMODE_NOBLEND;
	m_Blend_Pal=0;								//�f�t�H���g�̓u�����h���[�h�͖����A�p�����[�^��0
	/*�摜�X�v���C�g�Ɏg�������o�ϐ�*/
	m_image_handler=-1;							//LoadGraph�֐��̓G���[�ł̂�-1��f���̂�-1�ŏ����������ق������S
	m_magni_w=m_magni_h=1.0;					//�f�t�H���g�͓��{
	m_turn=false;								//�f�t�H���g�ł͔��]���Ȃ�
	m_trans=true;								//���ߏ����̓f�t�H���g�͍s��
	m_cx=0,m_cy=0;								//�ЂƂ܂�0�ŏ�����
	m_rad=0;									//�f�t�H���g�ł͉�]���Ȃ�

	/*�����X�v���C�g�Ɏg�������o�ϐ�*/
	m_text[0]='\0';
	m_fontname[0]='\0';						//�t�H���g�͋󕶎���BDx���C�u�����̃f�t�H���g��p����
	m_fontsize=DEFAULT_FONTSIZE;			//12���f�t�H���g

	/*�����E��`�X�v���C�g�Ɏg�������o�ϐ�*/
	m_w=m_h=0;									//�T�C�Y0�Őݒ�

	/*�~�̃X�v���C�g�Ɏg�������o�ϐ�*/
	m_radius=0;								//���a0�ŏ�����
	m_fill=true;
}



SpriteNode::~SpriteNode(void)
{	
	dprintfln("\t~SpriteNode();");
	/*���͐e�q�֌W�����Ȃ��B�ʓ|�����ǂ��ׂẴX�v���C�g���Ǘ�����
	delete Parent;
	Parent=0;
	for(double i=0;i<CHILDREN_MAX;i++){
		delete Children[i];
		Children[i]=0;
	}
	*/
	m_x=m_y=0;								//���W�͂ЂƂ܂�(0,0,0)��
	m_ID=0;
	m_type=NONE;								//���������X�v���C�g�Ƃ��Đݒ�
	m_color_r=m_color_g=m_color_b=0;			//�f�t�H���g�͍�
	m_Blend_Mode=DX_BLENDMODE_NOBLEND;
	m_Blend_Pal=0;								//�f�t�H���g�̓u�����h���[�h�͖����A�p�����[�^��0
	/*�摜�X�v���C�g�Ɏg�������o�ϐ�*/
	m_image_handler=-1;							//LoadGraph�֐��̓G���[�ł̂�-1��f���̂�-1�ŏ����������ق������S
	m_magni_w=m_magni_h=1.0;					//�f�t�H���g�͓��{
	m_turn=false;								//�f�t�H���g�ł͔��]���Ȃ�
	m_trans=true;								//���ߏ����̓f�t�H���g�͍s��
	m_cx=0,m_cy=0;								//�ЂƂ܂�0�ŏ�����
	m_rad=0;									//�f�t�H���g�ł͉�]���Ȃ�

	/*�����X�v���C�g�Ɏg�������o�ϐ�*/
	char* m_fontname="\0";						//�t�H���g�͋󕶎���BDx���C�u�����̃f�t�H���g��p����
	double m_fontsize=-1;							//-1�ŏ������ύX���������Dx���C�u�����̃f�t�H���g

	/*�����E��`�X�v���C�g�Ɏg�������o�ϐ�*/
	m_w=m_h=0;									//�T�C�Y0�Őݒ�

	/*�~�̃X�v���C�g�Ɏg�������o�ϐ�*/
	m_radius=0;								//���a0�ŏ�����
}
	/*�X�v���C�g�̐e�q�֌W�֐�*/
/*	���͐e�q�֌W�����Ȃ��B�ʓ|�����ǂ��ׂẴX�v���C�g���Ǘ�����
	void SpriteNode::Set_Parent(SpriteNode *parent){				//�e�X�v���C�g���Z�b�g
			Parent=parent;
	}
	void SpriteNode::add_Child(SpriteNode *child){	//�q�X�v���C�g�̒ǉ��B
		Children[children_count]=child;
		Children[children_count]->Set_Parent(this);
		children_count++;
	}
	void SpriteNode::remove_Child(SpriteNode *child){//�q�X�v���C�g�̍폜�B�q���폜���ꂽ�ꍇ���̎q��艺�ʑw�̃X�v���C�g���폜
	}
*/
/*���擾�֐�*/

	double SpriteNode::Get_W(){								//��`���̎擾
		if(m_type==LINE||m_type==BOX){
			return m_w;
		}
		printf("��`�܂��͒������[�h�łȂ����ߎ擾�o���܂���\n");
		return -1;
	}
	double SpriteNode::Get_H(){								//��`�����̎擾
		if(m_type==LINE||m_type==BOX){
			return m_h;
		}
		printf("��`�܂��͒������[�h�łȂ����ߎ擾�o���܂���\n");
		return -1;
	}	
	double SpriteNode::Get_Center_X(){							//���SX���W�̎擾
		if(m_type==IMAGE){
			return m_cx;
		}
		printf("�摜���[�h�łȂ����ߎ擾�o���܂���\n");
			return -1;
	}
	double SpriteNode::Get_Center_Y(){							//���SY���W�̎擾
		if(m_type==IMAGE){
			return m_cy;
		}
		printf("�摜���[�h�łȂ����ߎ擾�o���܂���\n");
			return -1;
	}
	double SpriteNode::Get_Radius(){							//���a���W�̎擾
		if(m_type==CIRCLE){
			return m_radius;
		}
		printf("�~���[�h�łȂ����ߎ擾�o���܂���\n");
			return -1;
	}

void SpriteNode::MoveTo(double x,double y){
	m_x=x;
	m_y=y;
}
void SpriteNode::Set_ID(int id){
	m_ID=id;
}
void SpriteNode::Change_Color(int r,int g,int b){							//�F�ݒ�
	if(m_type==IMAGE||m_type==NONE){
		printf("�J���[�̐ݒ肪�ł��Ȃ��^�C�v�ł� Type code:%d\n",m_type);
		return;
	}
	m_color_r=r;
	m_color_b=b;
	m_color_g=g;
}
void SpriteNode::Blend_Setting(int mode,int pal){							//�u�����h���[�h�̃Z�b�g�ƃp�����[�^�̐ݒ�
	m_Blend_Mode=mode;
	m_Blend_Pal=pal;
}
/*�摜�X�v���C�g�Ɏg�������o�֐�*/
void SpriteNode::init_Image(ImageLoader* loader,char* item_name){			//�A�C�e�����Ń��[�_�[����摜������Ă���B
	m_type=IMAGE;
	m_image_handler=loader->GetItemByName(item_name);
}
void SpriteNode::init_Image(ImageLoader* loader,char* item_name,int index){	//�A�C�e�����ƃC���f�b�N�X(0�X�^�[�g)�Ń��[�_�[���炪����������Ă���(add_divimage�œo�^�����^�C�v�̉摜)
	m_type=IMAGE;
	char name[256]="\0",number[NUMBER_MAX];
	sprintf_s(number,"%d",index);												//���l�𕶎�������
	strcat_s(name,item_name);
	strcat_s(name,number);												//���O�Ɛ�����A��
	m_image_handler=loader->GetItemByName(name);
}
void SpriteNode::Image_Rotate(double rad){									//�摜�̉�]�p(rad)��ݒ�
	if(m_type!=IMAGE){
		printf("�摜���[�h�ł͂Ȃ��̂Ŋp�x�ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return;
	}
	m_rad=rad;
}
void SpriteNode::Image_Magnificant(double w,double h){							//���ƃ^�e�̊g�嗦�ݒ�
	if(m_type!=IMAGE){
		printf("�摜���[�h�ł͂Ȃ��̂Ŋg�嗦�ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return;
	}
	m_magni_w=w;
	m_magni_h=h;
}
void SpriteNode::Image_Reverse(){											//���݂̏�Ԃ���摜�𔽓]
	if(m_type!=IMAGE){
		printf("�摜���[�h�ł͂Ȃ��̂Ŕ��]�ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_turn=!m_turn;
}
void SpriteNode::Image_Trans(bool flg){						//���ߏ������s�����ǂ�����ݒ�
	if(m_type!=IMAGE){
		printf("�摜���[�h�ł͂Ȃ��̂œ��ߏ����ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_trans=flg;
}
void SpriteNode::Image_Spin_Center(double cx,double cy){							//�摜����]�����钆�S�_
	if(m_type!=IMAGE){
		printf("�摜���[�h�ł͂Ȃ��̂ŉ�]���S�_�̐ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_cx=cx;
	m_cy=cy;
}
/*�����X�v���C�g�Ɏg�������o�֐�*/
void SpriteNode::init_Text(const char* text,...){										//��������Z�b�g
	m_type=TEXT;
	va_list ap ;

	va_start(ap,text) ;
    vsprintf_s(m_text,text,ap) ;
	va_end(ap) ;

}
void SpriteNode::Text_Font(char *fontname){									//�t�H���g�ݒ�
	if(m_type!=TEXT){
		printf("�������[�h�ł͂Ȃ��̂Ńt�H���g�ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	strcpy_s(m_fontname,_countof(m_fontname),fontname);
}
void SpriteNode::Text_Size(int size){										//�����T�C�Y�̐ݒ�
	if(m_type!=TEXT){
		printf("�������[�h�ł͂Ȃ��̂ŕ����T�C�Y�ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_fontsize=size;
}
/*�����E��`�X�v���C�g�Ɏg�������o�֐�*/
void SpriteNode::init_Line(double x,double y){									//(0,0)����̏I�[���W�Œ������Z�b�g
	m_type=LINE;
	m_w=x;
	m_h=y;
}
void SpriteNode::init_Box(double w,double h){										//���ƍ�����ݒ肵�ċ�`���Z�b�g
	m_type=BOX;
	m_w=w;
	m_h=h;
}
void SpriteNode::Box_Fill(bool flg){										//��`��h��Ԃ����ۂ�
	if(m_type!=BOX){
		printf("��`���[�h�ł͂Ȃ��̂œh��Ԃ��ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_fill=flg;
}
/*�~�X�v���C�g�Ɏg�������o�֐�*/
void SpriteNode::init_Circle(double r){										//�~�̔��a��ݒ�
	m_type=CIRCLE;
	m_radius=r;
}
void SpriteNode::Circle_Fill(bool flg){										//�~��h��Ԃ����ۂ�
	if(m_type!=CIRCLE){
		printf("�~���[�h�ł͂Ȃ��̂œh��Ԃ��ݒ肪�ł��܂��� Type code:%d\n",m_type);
		return ;
	}
	m_fill=flg;
}

/*�_�X�v���C�g�Ɏg�������o�֐�*/

void SpriteNode::init_Pixel(){
	m_type=PIXEL;
}

/*�����\�����Ȃ��X�v���C�g�Ƃ��ď���������B�ė��p���鎞�̂��߂ɂ��ׂď���������B���W�Ȃǂ̃p�����[�^�͂��̂܂�*/
void SpriteNode::init_None(){
	m_type=NONE;								//���������X�v���C�g�Ƃ��Đݒ�
}

void SpriteNode::DrawThis(){
	int color=GetColor(m_color_r,m_color_g,m_color_b);
	SetDrawBlendMode(m_Blend_Mode,m_Blend_Pal);
	/*�^�C�v�����ĕ`����@��ς���*/
	switch(m_type){
	case IMAGE:
		DrawRotaGraph3((int)m_x,(int)m_y,(int)m_cx,(int)m_cy,m_magni_w,m_magni_h,m_rad,m_image_handler,m_trans,m_turn) ;
		break;
	case TEXT:
			SetFontSize(m_fontsize);
			ChangeFont(m_fontname);
		DrawString((int)m_x,(int)m_y,m_text,color);
		break;
	case LINE:
		DrawLine((int)m_x,(int)m_y,(int)(m_x+m_w),(int)(m_y+m_h),color);
		break;
	case BOX:
		DrawBox((int)m_x,(int)m_y,(int)(m_x+m_w),(int)(m_y+m_h),color,m_fill);
		break;
	case CIRCLE:
		DrawCircle((int)m_x,(int)m_y,(int)m_radius,color,m_fill);
		break;
	case PIXEL:
		DrawPixel((int)m_x,(int)m_y,color);
		break;
	/*�^�C�v��NONE�A���邢�͖����ꑶ�݂��Ȃ����[�h���w�肳��Ă���΃G���[��f���B�q�X�v���C�g�������Ȃ�*/
	case NONE:
		break;
	default:
		printf("�X�v���C�g���ݒ肳��Ă��܂���\n");
		return;
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,m_Blend_Pal);
	
}

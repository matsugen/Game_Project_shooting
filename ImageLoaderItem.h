#pragma once
#include"stdafx.h"
class ImageLoaderItem
{

private:
	static int m_count;							//imageloaderitem�̑����B�f�o�b�O�p
	int image_handler;							//�摜�n���h��
	char image_name[STRING_MAX];				//�摜�̖��O(����������Č���)
public:
	ImageLoaderItem(void);
	~ImageLoaderItem(void);
	void init(int handler,char *image_name);	//�A�C�e�������Z�b�g����B
	int Handler(){return image_handler;}		//�n���h���̎擾
	char* Name(){return image_name;}			//�摜�̖��O�̎擾
};


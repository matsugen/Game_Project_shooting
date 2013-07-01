#include "StdAfx.h"
#include "ImageLoaderItem.h"

int ImageLoaderItem::m_count=0;

ImageLoaderItem::ImageLoaderItem(void)
{
	m_count++;
	dprintfln("ImageLoaderItem():%d;",m_count);
	image_handler=-1;
	image_name[0]='\0';
}


ImageLoaderItem::~ImageLoaderItem(void)
{
	dprintfln("~ImageLoaderItem();");
	DeleteGraph(image_handler);
}

void ImageLoaderItem::init(int handler,char *name){
	char tmp_name[256];
	image_handler=handler;
	strcpy_s(tmp_name,name);
	strcpy_s(image_name,tmp_name);
}
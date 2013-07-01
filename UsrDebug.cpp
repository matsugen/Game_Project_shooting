
#include"stdafx.h"
#include"UsrDebug.h"
void dprintfln(const char *format,...)
{
  char data[STRING_MAX] ;
  va_list ap ;

  va_start(ap,format) ;
    vsprintf_s(data,format,ap) ;
  va_end(ap) ;

  OutputDebugStringA(data) ;
  OutputDebugStringA("\n") ;
}
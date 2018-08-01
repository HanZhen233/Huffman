#ifndef COMPRESS_H
#define COMPRESS_H
#include"compress.h"
#include "huffman.h"
//文件头
struct HEAD
{
	char aType[4];
	int nLength;
	int len;
	int aWeight[256];
};

//缓冲区
typedef char *BUFFER;
//功能函数
//压缩文件
int compress(const char *filename);
//初始化文件头
int initHead(const char *filename,HEAD &sHead);
//对文件进行文件压缩
int Encode(const char *filename,HCode pHC, BUFFER &pBuffer,const int nSize );
//将字符串转化成字节
char str2byte(const char *pBinStr);
int WriteFile(const char *pFilename,const HEAD sHead,const BUFFER pBuffer,const int nSize);
//void test(HTree pHT);

#endif
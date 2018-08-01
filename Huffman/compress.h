#ifndef COMPRESS_H
#define COMPRESS_H
#include"compress.h"
#include "huffman.h"
//�ļ�ͷ
struct HEAD
{
	char aType[4];
	int nLength;
	int len;
	int aWeight[256];
};

//������
typedef char *BUFFER;
//���ܺ���
//ѹ���ļ�
int compress(const char *filename);
//��ʼ���ļ�ͷ
int initHead(const char *filename,HEAD &sHead);
//���ļ������ļ�ѹ��
int Encode(const char *filename,HCode pHC, BUFFER &pBuffer,const int nSize );
//���ַ���ת�����ֽ�
char str2byte(const char *pBinStr);
int WriteFile(const char *pFilename,const HEAD sHead,const BUFFER pBuffer,const int nSize);
//void test(HTree pHT);

#endif
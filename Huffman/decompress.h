#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include"huffman.h"
#include"compress.h"
int decompress(const char *pFilename);
int initFile(const char *pFilename,HCode &pHC,HEAD &sHead,BUFFER &pBuffer);
int Decode(const char *pFilename,HCode pHC,BUFFER pBuffer,BUFFER &nBuffer,HEAD sHead,HTree pHT);
char* Byte2str(char b);
int  writeFile(const char *pFilename,HEAD sHead,BUFFER nBuffer);
#endif
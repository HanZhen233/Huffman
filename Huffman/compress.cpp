#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include"compress.h"
#include"huffman.h"
#include"global.h"

using namespace std;






//压缩文件
int  compress(const char *filename){
	HEAD sHead;
	if(ERROR==initHead(filename,sHead))
		return ERROR;
	cout<<sHead.nLength<<"字节"<<endl;
	//生成Huffman树
	HTree pHT=NULL;
	HuffmanTree(pHT,sHead.aWeight);
	//test(pHT);//测试树是否已经生成好
	if(!pHT)
		return ERROR;
	//生成Huffman编码
	HCode pHC=NULL;
	HuffmanCoding(pHC,pHT);
	free(pHT);//释放Huffman树空间
	if(!pHC)
		return ERROR;

	//计算编码缓存区的大小
	for(int i=0;i<256;i++){
	cout<<i+1<<" "<<pHC[i+1]<<endl;
	}
	int nSize=0;
	for(int i=0;i<256;i++){
		nSize+=sHead.aWeight[i]*strlen(pHC[i+1]);
	}
	 
	nSize=nSize%8?nSize/8+1:nSize/8;

	//对源文件进行编码压缩
	BUFFER pBuffer=NULL;
	
	Encode(filename,pHC,pBuffer,nSize);
	for(int i=1;i<=256;i++)
	free(pHC[i]);
 
	if(!pBuffer)
		return ERROR;
	sHead.len=nSize;//记录压缩后实际长度（不算头文件及文件名）
	int len= WriteFile(filename,sHead,pBuffer,nSize);
	free(pBuffer);
	if(len<0)
		return ERROR;
	cout<<len<<"字节";
	cout<<""<<(double)len/(double)sHead.nLength*100<<"%"<<endl;
	return OK;

}







int initHead(const char *filename,HEAD &sHead){
	strcpy(sHead.aType,"HUF");
	sHead.nLength=0;
	for(int i=0;i<SIZE;i++)
		sHead.aWeight[i]=0;
	FILE *in=fopen(filename,"rb");
	if(!in){
		cerr<<"初始化文件头失败！"<<endl;
		return ERROR;
	}
	//扫描文件，统计次数
	int ch;
	while((ch=fgetc(in))!=EOF)
	{
		sHead.aWeight[ch]++;
		sHead.nLength++;
	}
	fclose(in);
	in=NULL;
	return OK;
}

int Encode(const char *filename,HCode pHC, BUFFER &pBuffer,const int nSize ){
		FILE *in=fopen(filename,"rb");
	if(!in){
		cerr<<"打开源文件失败！"<<endl;
		return ERROR;
	}
	//开辟缓冲区
	pBuffer=(char*)malloc(nSize*sizeof(char));
	//cout<<nSize<<endl;
	if(!pBuffer){
		cerr<<"开辟缓存空间失败！"<<endl;
		return ERROR;
	}
	//扫描文件，根据Huffman编码进行压缩，结果暂存在缓冲区
		char cd[SIZE]={0};
		int pos=0;
		int ch;
	while((ch=fgetc(in))!=EOF)
	{
		strcat(cd,pHC[ch+1]);
		while(strlen(cd)>=8)
		{
			
			pBuffer[pos++]=str2byte(cd);
			//printf("0x%02X\n", pBuffer[pos-1]);
			for(int i=0;i<SIZE-8;i++)
			{
				cd[i]=cd[i+8];
			}
		}
	}
		if(strlen(cd)>0)
	{
		pBuffer[pos++]=str2byte(cd);
	}
	
		/*
		while (fread(&ch, 1, 1, in))
	{
		strcat(cd,pHC[ch+1]);
		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = str2byte(cd);
			//printf("0x%02X\n", pBuffer[pos-1]);
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = str2byte(cd);
	}
	*/
		//cout<<pos<<endl;
		//printf("0x%02X\n", pBuffer[1000]);
	fclose(in);

	return OK;

}



//将0101..转化成字节
char str2byte(const char *pBinStr){
    /*char b = 0x00;
	for (int i = 0;i < 8; i++)
	{

		b = b << 1;//左移一位
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	//printf("0x%02X\n", b);
	return b;
	*/

	char b=0;
	for(int i=0;i<8;i++){
		if(pBinStr[i]=='1'){
			b+=(char)pow(2,7-i);
		}
	}
	return b;
}


//写文件
int WriteFile(const char *pFilename,const HEAD sHead,const BUFFER pBuffer,const int nSize){

	char filename[256]={0};
	strcpy(filename,pFilename);
	strcat(filename,".huf");
	//以二进制流打开文件
	FILE *out=fopen(filename,"wb");
	if(!out){
		cerr<<"写入文件失败！"<<endl;
		return ERROR;
	}

	
	//写入文件头
	fwrite(&sHead,sizeof(HEAD),1,out);
	//写入压缩后的编码
	
	fwrite(pBuffer,sizeof(char),nSize,out);
	//cout<<pBuffer[100]<<endl;;
	fclose(out);
	out=NULL;

	cout<<"生成压缩文件："<<filename<<endl;
	int len=sizeof(HEAD)+strlen(pFilename)+1+nSize;
	return len;
}

//测试树
/*void test(HTree pHT){

for(int i=1;i<512;i++)

	cout<<i<<" "<<pHT[i].nParent<<" "<<pHT[i].nWeight<<" "<<pHT[i].nLChild<<" "<<pHT[i].nRChild<<endl;
}*/



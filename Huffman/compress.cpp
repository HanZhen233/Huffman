#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include"compress.h"
#include"huffman.h"
#include"global.h"

using namespace std;






//ѹ���ļ�
int  compress(const char *filename){
	HEAD sHead;
	if(ERROR==initHead(filename,sHead))
		return ERROR;
	cout<<sHead.nLength<<"�ֽ�"<<endl;
	//����Huffman��
	HTree pHT=NULL;
	HuffmanTree(pHT,sHead.aWeight);
	//test(pHT);//�������Ƿ��Ѿ����ɺ�
	if(!pHT)
		return ERROR;
	//����Huffman����
	HCode pHC=NULL;
	HuffmanCoding(pHC,pHT);
	free(pHT);//�ͷ�Huffman���ռ�
	if(!pHC)
		return ERROR;

	//������뻺�����Ĵ�С
	for(int i=0;i<256;i++){
	cout<<i+1<<" "<<pHC[i+1]<<endl;
	}
	int nSize=0;
	for(int i=0;i<256;i++){
		nSize+=sHead.aWeight[i]*strlen(pHC[i+1]);
	}
	 
	nSize=nSize%8?nSize/8+1:nSize/8;

	//��Դ�ļ����б���ѹ��
	BUFFER pBuffer=NULL;
	
	Encode(filename,pHC,pBuffer,nSize);
	for(int i=1;i<=256;i++)
	free(pHC[i]);
 
	if(!pBuffer)
		return ERROR;
	sHead.len=nSize;//��¼ѹ����ʵ�ʳ��ȣ�����ͷ�ļ����ļ�����
	int len= WriteFile(filename,sHead,pBuffer,nSize);
	free(pBuffer);
	if(len<0)
		return ERROR;
	cout<<len<<"�ֽ�";
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
		cerr<<"��ʼ���ļ�ͷʧ�ܣ�"<<endl;
		return ERROR;
	}
	//ɨ���ļ���ͳ�ƴ���
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
		cerr<<"��Դ�ļ�ʧ�ܣ�"<<endl;
		return ERROR;
	}
	//���ٻ�����
	pBuffer=(char*)malloc(nSize*sizeof(char));
	//cout<<nSize<<endl;
	if(!pBuffer){
		cerr<<"���ٻ���ռ�ʧ�ܣ�"<<endl;
		return ERROR;
	}
	//ɨ���ļ�������Huffman�������ѹ��������ݴ��ڻ�����
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



//��0101..ת�����ֽ�
char str2byte(const char *pBinStr){
    /*char b = 0x00;
	for (int i = 0;i < 8; i++)
	{

		b = b << 1;//����һλ
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


//д�ļ�
int WriteFile(const char *pFilename,const HEAD sHead,const BUFFER pBuffer,const int nSize){

	char filename[256]={0};
	strcpy(filename,pFilename);
	strcat(filename,".huf");
	//�Զ����������ļ�
	FILE *out=fopen(filename,"wb");
	if(!out){
		cerr<<"д���ļ�ʧ�ܣ�"<<endl;
		return ERROR;
	}

	
	//д���ļ�ͷ
	fwrite(&sHead,sizeof(HEAD),1,out);
	//д��ѹ����ı���
	
	fwrite(pBuffer,sizeof(char),nSize,out);
	//cout<<pBuffer[100]<<endl;;
	fclose(out);
	out=NULL;

	cout<<"����ѹ���ļ���"<<filename<<endl;
	int len=sizeof(HEAD)+strlen(pFilename)+1+nSize;
	return len;
}

//������
/*void test(HTree pHT){

for(int i=1;i<512;i++)

	cout<<i<<" "<<pHT[i].nParent<<" "<<pHT[i].nWeight<<" "<<pHT[i].nLChild<<" "<<pHT[i].nRChild<<endl;
}*/



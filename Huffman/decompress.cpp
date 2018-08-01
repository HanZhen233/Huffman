#include<iostream>
#include<cstring>
#include"decompress.h"
#include"global.h"
#include"huffman.h"
#include"compress.h"
using namespace std;

void test(HTree pHT){

for(int i=1;i<512;i++){

	cout<<i<<" "<<pHT[i].nParent<<" "<<pHT[i].nWeight<<" "<<pHT[i].nLChild<<" "<<pHT[i].nRChild<<endl;
}

}
int decompress(const char *pFilename){

	HCode pHC=NULL;
	HTree pHT=NULL;
    BUFFER pBuffer=NULL,nBuffer=NULL;
	HEAD sHead;

	initFile(pFilename,pHC,sHead,pBuffer);//���ļ�ͷ�ж�ȡͷ������hufman�����Լ���ȡ�ļ�����������
	HuffmanTree(pHT,sHead.aWeight);//����Huffmman��
	test(pHT);//�������Ƿ��Ѿ����ɺ�
	if(!pHT)
		return ERROR;
	//����Huffman����
	nBuffer=(char*)malloc(sizeof(char)*sHead.nLength);
	 Decode(pFilename,pHC,pBuffer,nBuffer,sHead,pHT);//���ԭ�ļ������ݲ������ڻ�����
	 writeFile(pFilename,sHead,nBuffer);//д���ļ�

	 free(nBuffer);
	 for(int i=1;i<=256;i++){
	 free(pHC[i]);
	 }
	 free(pHT);
	return OK;
} 



int initFile(const char *pFilename,HCode &pHC,HEAD &sHead, BUFFER &pBuffer){
	int nSize;
	HTree pHT=NULL;
	FILE *in=fopen(pFilename,"rb");
	if(!in){
		cerr<<"��ȡ�ļ�ʧ�ܣ�"<<endl;
		return ERROR;
	}
	fread(&sHead,sizeof(HEAD),1,in);
	//cout<<sHead.len<<endl;
	//cout<<sHead.nLength<<endl;
	//cout<<sHead.aWeight[0]<<endl;
    nSize=sHead.len;//ѹ�������ĳ���

	//������������
	HuffmanTree(pHT,sHead.aWeight);
		if(!pHT)
		return ERROR;
	//����Huffman����
	HuffmanCoding(pHC,pHT);
	
	if(!pHC)
		return ERROR;

	cout<<nSize<<endl;
	//��ȡ�������ݣ������뻺��
	pBuffer=(char*)malloc(nSize*sizeof(char));
	if(!pBuffer){
		cerr<<"���ٻ���ռ�ʧ�ܣ�"<<endl;
		return ERROR;
	}
	fread(pBuffer,sizeof(char),nSize,in);
	fclose(in);
	free(pHT);//�ͷ�Huffman���ռ�
	return OK;
}


int Decode(const char *pFilename,HCode pHC,BUFFER pBuffer,BUFFER &nBuffer,HEAD sHead,HTree pHT)
{
	int l=0;
	int j=0;
	int s=0;
	int p=511;
	int flag=0;

	BUFFER sBuffer=(char*)malloc(sizeof(char)*(8*sHead.len+1));
	sBuffer[0] ='\0';
	for(int i=0;i<sHead.len;i++){//���ַ�ת����0101...�Ȳ����ڻ�������
	strcat(sBuffer,Byte2str(pBuffer[i]));
	}


	char a[256]={'\0'};

	while(sBuffer[l]!='\0'){
	a[j]=sBuffer[l];
	for(int z=0;z<=j;z++){
		if(a[z]=='0')
		p=pHT[p].nLChild;
		if(a[z]=='1')
		p=pHT[p].nRChild;
		}
	if(pHT[p].nLChild==0){
	
	    nBuffer[s++]=(p-1);
		memset(a,0x00,sizeof(char)*256);
		j=-1;
	}
	p=511;

/*	for(int k=1;k<=256;k++){
		if(!strcmp(a,pHC[k])){
		nBuffer[s++]=k;
			memset(a,0x00,sizeof(char)*256);
			j=-1;
			break;
		}
	 }
	 */
	j++;
	l++;
	}

	free(sBuffer);
	
	return OK;
}



char* Byte2str(char b){//�ַ�ת���ɶ������ַ���
	char *p=(char*)malloc(sizeof(char)*9);
	for(int i=7;i>=0;i--){
	if(b%2==1)
	p[i]='1';
	else
		p[i]='0';
	b=b/2;
	}
	p[8]='\0';
	return p;
}


int  writeFile(const char *pFilename,HEAD sHead,BUFFER nBuffer){
	char filename[256]={0};
	strncpy(filename,pFilename,strlen(pFilename)-strlen(".hub"));

	FILE *out=fopen(filename,"wb");
	if(!out){
		cerr<<"��ȡ�ļ�ʧ�ܣ�"<<endl;
		return ERROR;
	}

	fwrite(nBuffer,sizeof(char),sHead.nLength,out);
	//cout<<pBuffer[100]<<endl;;
	fclose(out);
	out=NULL;
	return OK;
}

# include<iostream>
#include"global.h"
#include<stdio.h>
#include"huffman.h"
#include"compress.h"
using namespace std;
int HuffmanTree(HTree &pHT,int *aWeight){
	int m=2*SIZE-1;
	pHT=(HTree)malloc((m+1)*sizeof(HTNode));
	if(!pHT){
		cerr<<"�ڴ����ʧ��ʧ�ܣ�"<<endl;
		return ERROR;
	}
	//��ʼ������1-511
	HTree p=pHT+1;
	for(int i=0;i<m;i++){
		p->nWeight=(i<SIZE)?aWeight[i]:0;
		p->nParent=0;
		p->nLChild=0;
		p->nRChild=0;
	    p++;
	}
	//����Huffman��
	for(int i=SIZE+1;i<=m;i++){//��257��ʼʹ֮ǰ������������
	 int s1=Select(pHT,i-1);
	 pHT[s1].nParent=i;
	 int s2=Select(pHT,i-1);
	 pHT[s2].nParent=i;
	 pHT[i].nWeight=pHT[s1].nWeight+pHT[s2].nWeight;
	 pHT[i].nLChild=s1;
	 pHT[i].nRChild=s2;
	}
	return OK;
}


int Select(HTree pHT,int nSize){
	int minValue=0x7FFFFFFF;
	int min=0;
	for(int i=1;i<=nSize;i++){
		if(pHT[i].nParent==0&&(pHT[i].nWeight<minValue))
		{
			minValue=pHT[i].nWeight;
			min=i;
		}
	}

	return min;
}

int HuffmanCoding(HCode &pHC,HTree pHT){
		pHC=(char**)malloc(256*sizeof(char*));
	char cd[SIZE]={'\0'};
	int cdlen=0;
	for(int i=1;i<512;i++){
		pHT[i].nWeight=0;//������Ȩֵ�û������Խ�ʡ�ռ������ʱ�־λ
	}
	int p=511;
	while(p!=0){
		if(pHT[p].nWeight==0){
			pHT[p].nWeight=1;//��ʾ�Ѿ�����������˵�
			if(pHT[p].nLChild!=0){
				p=pHT[p].nLChild;
				cd[cdlen++]='0';
			}
			else if(pHT[p].nRChild==0){
				pHC[p]=(char*)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0';
				strcpy(pHC[p],cd);
			}
		}
		else if(pHT[p].nWeight==1)
		{
			pHT[p].nWeight=2;
			if(pHT[p].nRChild!=0){
				p=pHT[p].nRChild;
				cd[cdlen++]='1';
			}
		}
		else
		{
			pHT[p].nWeight=0;
			p=pHT[p].nParent;
			--cdlen;
		}
	}

	return OK;
}
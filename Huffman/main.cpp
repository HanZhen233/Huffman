#include<iostream>
#include"compress.h"
#include"decompress.h"
using namespace std;
int main(){
	
	char filename[256];
	char dFilename[256];
	int i=-1;
	while(i!=0)
	{
		cout<<"----------ͼƬ����ѹ�����ѹ----------"<<endl<<endl;
		cout<<"1.�ļ�ѹ��"<<endl;
		cout<<"2.�ļ���ѹ"<<endl;
		cout<<"0.�˳�"<<endl;
		cin>>i;
		switch(i){

		case 1:
	    cout<<"----------ͼƬѹ��----------"<<endl;
	    cout<<"�������ļ�����";
	    cin>>filename;
	    compress(filename);
	    break;
		case 2:
		cout<<"----------ͼƬ��ѹ----------"<<endl;
	    cout<<"�������ļ�����";
	    cin>>dFilename;
	    decompress(dFilename);
		}
	}
   return 0;
}

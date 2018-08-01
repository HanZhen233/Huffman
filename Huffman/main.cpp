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
		cout<<"----------图片编码压缩与解压----------"<<endl<<endl;
		cout<<"1.文件压缩"<<endl;
		cout<<"2.文件解压"<<endl;
		cout<<"0.退出"<<endl;
		cin>>i;
		switch(i){

		case 1:
	    cout<<"----------图片压缩----------"<<endl;
	    cout<<"请输入文件名：";
	    cin>>filename;
	    compress(filename);
	    break;
		case 2:
		cout<<"----------图片解压----------"<<endl;
	    cout<<"请输入文件名：";
	    cin>>dFilename;
	    decompress(dFilename);
		}
	}
   return 0;
}

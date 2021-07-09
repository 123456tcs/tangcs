#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
	unsigned int filesize(int fd);  //声明函数
	unsigned int readfile(int fd,int len,char data[]);
	unsigned int writefile(int fd,int a,char data[]);

	int fd1, fd2, len2, offset;
	char file1name[20],file2name[20];

	printf("请输入文件1和文件2名称：\n");
	fgets(file1name,20,stdin);
	fgets(file2name,20,stdin);
	file1name[strlen(file1name)-1] = '\0';
	file2name[strlen(file2name)-1] = '\0';
	printf("请输入offset值：\n");
	scanf("%d",&offset);

	fd1 = open(file1name,O_RDWR,S_IRWXU);
	fd2 = open(file2name,O_RDWR,S_IRWXU);
	if((fd1 == -1) || (fd2 == -1))
	{
		printf("打开文件错误\n");
		exit(0);
	}

	len2 = filesize(fd2);
        char data[len2+1];
	printf("要粘贴的文件长度为：%d\n",len2);

	readfile(fd2,len2,data);
	writefile(fd1,offset,data);

	close(fd1);
	close(fd2);
}

unsigned int filesize(int fd)//返回文件长度函数
{
	int len;

	len = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	return len;
}

unsigned int readfile(int fd,int len,char data[])//读文件内容到缓存data
{
	int i;
	i = read(fd,data,len);
	if(i<0)
	{
		printf("读文件失败！\n");
		exit(0);
	}
	data[len] = '\0';//防止结尾乱码
}

unsigned int writefile(int fd,int a,char data[])//写缓存data到文件
{
	lseek(fd,a,SEEK_SET);

	if(write(fd,data,strlen(data)) != strlen(data))
	{
		printf("写入失败！\n");
		exit(0);
	}
	else printf("写入成功！\n");
}


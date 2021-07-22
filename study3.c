#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd;
	unsigned char * p = NULL;
	unsigned long addr;
	fd = open("/dev/mem",O_RDWR|O_SYNC);//打开/dev/mem并设置打开方式为可读可写和以同步方式打开
	if(fd == -1)
	{
		printf("打开/dev/men失败\n");
		return -1;
	}

	p = mmap(0,0x1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x20000);//创建映射区
	if(p == MAP_FAILED)
	{
		printf("映射错误\n");
		return -1;
	}
	else   
	{
		printf("映射成功\n");
	}

	unsigned long i = 0x1;                 //地址偏移
	unsigned long a = 0x01;                 //给地址要赋的值
	unsigned char origin;                 //初始地址的值

	addr=(unsigned long)(p+i);
	origin=p[i];

	printf("addr:0x%lx\t",addr);
	printf("before change content:0x%lx\n",(unsigned long)p[i]);  //输出映射到的虚拟地址，以及这个地址当前的内容

	p[i]=(unsigned char)a;
	printf("addr:0x%lx\t",addr);
	printf("after change content:0x%lx\n",(unsigned long)p[i]);  //随便给这个地址赋值，修改地址内容

	p[i]=origin;
	printf("addr:0x%lx\t",addr);
	printf("final content:0x%lx\n",(unsigned long)p[i]);  //把地址内容复原回去，因为是随便映射的地址，不知道这个地址储存的是不是重要内容，所以复原，以防造成破坏
	
	munmap(p, 0x1);//关闭映射
	close(fd);     //关闭/dev/mem

	return 0;
}

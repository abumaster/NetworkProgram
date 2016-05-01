/*
 * 多用户的服务器程序
 * 通过为每个客户端创建新的进程
*/
#include "unp.h"

#define LISTEN_PORT 6000
#define MAX_LE 5

void str_echo(int sockfd)//从sockfd中读取数据
{
	int n;
	char line[512];
	pid_t pid;
	printf("开始读取数据...");
	while (1)
	{
		while ((n=read(sockfd,line,512))>0)//有数据
		{
			line[n]='\0';
			printf("Client Send: %s\n",line);
			bzero(&line,sizeof(line));
		}
	}
}

int main(int argc, char **argv)
{
	int listenfd,connfd;
	pid_t childid;
	socklen_t chilen;

	struct sockaddr_in chiaddr,servaddr;
	
	//1.创建套接字
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if (listenfd==-1)
	{
		err_quit("创建套接字失败");
	}
	//2.初始化地址信息
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(LISTEN_PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(servaddr.sin_zero),8);
	//3.绑定
	if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
	{
		printf("bind失败");
		exit(1);
	}
	//4.监听
	if (listen(listenfd,MAX_LE)==-1)
	{
		printf("listen失败");
		exit(1);
	}
	//5.等待连接
	while (1)
	{
		chilen=sizeof(chiaddr);

		if ((connfd=accept(listenfd,(struct sockaddr*)&chiaddr,&chilen))==-1)
		{
			printf("accept 失败");
			exit(1);
		}
		else {
			printf("成功连接\n");
		}
		//创建子进程来处理信息
		if ((childid=fork())==0)//子
		{
			close(listenfd);//关闭连接
			printf("Client from %s\n",inet_ntoa(chiaddr.sin_addr));
			str_echo(connfd);
			exit(0);
		}
		else if (childid<0)
		{
			printf("fork 失败");
			close(connfd);
			exit(1);
		}
		close(connfd);
	}
	return 0;
}
	


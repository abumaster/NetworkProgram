/*
 * 客户程序
*/
#include "unp.h"

#define SER_PORT 6000

int my_str_cli( char * data, int sockfd)
{   
    while(1)
    {
       write(sockfd, data, strlen( data ) );
       sleep(1);
    }
   
    exit(0);
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in seraddr;

	if (argc!=3)
	{
		err_quit("Usage: myclient IP data");
	}

	//1.创建套接字
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		err_quit("创建套接字失败");
	}

	//2.初始化服务器地址信息
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SER_PORT);
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr);

	printf("Client connecting...\n");
	//3.连接服务器
	if (connect(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
	{
		printf("connect 失败");
		exit(1);
	}
	printf("开始发送数据");
	my_str_cli(argv[2],sockfd);
	return 0;
}

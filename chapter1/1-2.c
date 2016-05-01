/*
 * 一个简单的获取时间的客户程序
 * 此程序作为客户端，服务器为远程的主机的时间服务
 * 端口为13
 */
#include "unp.h"

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvbuf[MAXLINE+1];
	struct sockaddr_in servaddr;
	
	if (argc!=2)
		err_quit("Usag: a.out IP");
	
	// 1.创建套接字
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
		err_sys("socket error");
	// 2.初始化服务器地址
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(13);
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
		err_quit("inet_pton error for %s",argv[1]);
	// 3.连接服务器
	if (connect(sockfd, (SA *)&servaddr,sizeof(servaddr))<0)
		err_sys("connect error");
	// 4.读取数据
	while ((n=read(sockfd,recvbuf,MAXLINE))>0) {
		recvbuf[n]=0;
		if (fputs(recvbuf,stdout)==EOF)
			err_sys("fputs error");
	}
	if (n<0)
		err_sys("read error");
	exit(0);
}

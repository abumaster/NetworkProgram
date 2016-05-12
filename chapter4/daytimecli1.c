#include "unp.h"

extern int mysocket(int family, int type, int protocd);
extern void myconnect(int sockfd,const struct sockaddr *seraddr,socklen_t addrlen);
extern void myWrite(int filed, const void *buf, size_t len);
extern void myRead(int filed, void *buf, size_t len);

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvbuf[MAXLINE+1];
	struct sockaddr_in servaddr;
	
	if (argc!=2)
		err_quit("Usag: a.out IP");
	sockfd = mysocket(AF_INET,SOCK_STREAM,0);
	//初始化服务器地址信息
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
		err_quit("inet_pton error for %s",argv[1]);
	myconnect(sockfd,(SA*)&servaddr,sizeof(servaddr));
	myRead(sockfd,recvbuf,MAXLINE);
	close(sockfd);
	exit(0);
}

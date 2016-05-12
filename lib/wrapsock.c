#include "unp.h"

//包裹函数
int mysocket(int family, int type, int protocd)
{
	int n;
	if ((n = socket(family,type,protocd)) < 0) 
	  err_sys("socket error");
	return n;//返回套接
}
void mybind(int sockfd,const struct sockaddr *myaddr,socklen_t addrlen)
{
	int n;
	if ((n=bind(sockfd,myaddr,addrlen))<0)
	  err_sys("bind error");
}
void mylisten(int fd,int backlog)
{
	char *ptr;
	if ((ptr=getenv("LISTENQ"))!=NULL)
	  backlog = atoi(ptr);
	if (listen(fd,backlog)<0)
	  err_sys("listen error");
}
int myaccept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int n;
	if ((n=accept(sockfd,cliaddr,addrlen))<0)
	  err_sys("accept error");
	return n;//返回连接套接字
}
void myconnect(int sockfd,const struct sockaddr *seraddr,socklen_t addrlen)
{
	int n;
	if ((n=connect(sockfd,seraddr,addrlen))<0)
	  err_sys("connect error");
}
void myWrite(int filed, const void *buf, size_t len)
{
	int n;
	if ((n=write(filed,buf,len)) < 0)
	  err_sys("write error");
}
void myRead(int filed, void *buf, size_t len)
{
	int n;
	if ((n=read(filed,buf,len)) < 0)
	  err_sys("read error");
	else {
	  //buf[n]=0;
	  if (fputs(buf,stdout)==EOF)
	  err_sys("fputs error");
	}
}

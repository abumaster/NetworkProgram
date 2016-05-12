//daytime service 
#include "unp.h"
#include <time.h>

extern int mysocket(int family, int type, int protocd);
extern void mybind(int sockfd,const struct sockaddr *myaddr,socklen_t addrlen);
extern void mylisten(int fd,int backlog);
extern int myaccept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
extern void myconnect(int sockfd,const struct sockaddr *seraddr,socklen_t addrlen);
extern void myWrite(int filed, const void *buf, size_t len);
extern void myRead(int filed, void *buf, size_t len);
int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	listenfd = mysocket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	mybind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	mylisten(listenfd,5);
	
	for(; ;) {
		len = sizeof(cliaddr);
		connfd = myaccept(listenfd,(SA*) &cliaddr, &len);
		printf("connect from %s ,port %d \n",
		inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff)),
		ntohs(cliaddr.sin_port));
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
		myWrite(connfd,buff,strlen(buff));
		close(connfd);
	}
	close(listenfd);
	exit(0);
}

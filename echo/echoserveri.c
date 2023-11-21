#include "csapp.h"

// echo: 클라이언트 요청을 처리함
void echo(int connfd);

// main: 서버 프로그램의 entry point
int main(int argc, char **argv)
{
    // 리스닝 및 연결용 파일 디스크립터 선언
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; /* 모든 주소를 위한 충분한 공간 */
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // 리스닝 파일 디스크립터 열기
    listenfd = Open_listenfd(argv[1]); // argv[0] = ./echoserveri | argv[1] = 포트번호
    printf("listening file descriptor: %d\n", listenfd);
    while (1) {
        // 클라이언트 요청을 처리하기 위한 무한 루프
        clientlen = sizeof(struct sockaddr_storage);
        printf("연결 요청 대기 중\n");
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("연결 요청 수락, 연결 소켓(connfd) 생성\n");
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connectd to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}

// 에코 함수: 클라이언트 요청을 처리함
void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %d bytes\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}

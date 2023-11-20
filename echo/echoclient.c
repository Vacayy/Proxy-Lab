#include "csapp.h"

// main: 클라이언트 프로그램의 entry point
int main(int argc, char **argv)
{
    // 클라이언트 파일 디스크립터 선언
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3){
        fprintf(stderr, "usage: %s <host> <port> \n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    // 클라이언트 파일 디스크립터 열기
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    // 사용자의 입력을 읽고 서버로 전송
    while (Fgets(buf, MAXLINE, stdin) != NULL){
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    Close(clientfd);
    exit(0);
}
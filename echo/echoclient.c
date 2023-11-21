#include "csapp.h"

// main: 클라이언트 프로그램의 entry point
int main(int argc, char **argv)
{
    // 클라이언트 파일 디스크립터 선언
    int clientfd;
    char *host, *port, buf[MAXLINE]; // MAXLINE = 8192
    /* 서버는 최대 4096 byte 까지밖에 못받음*/
    rio_t rio; // Robust I/O = 네트워크 프로그래밍에서의 입출력 방식

    if (argc != 3){ // 호스트, 포트, 프로그램 이름 3개의 인자 필요
        fprintf(stderr, "usage: %s <host> <port> \n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    // 클라이언트 파일 디스크립터 열기
    clientfd = Open_clientfd(host, port); // p.903 -> 연결될 때까지 리스트의 주소 다 테스트
    Rio_readinitb(&rio, clientfd); // RIO 버퍼 초기화. 

    // 사용자의 입력을 읽고 서버로 전송
    while (Fgets(buf, MAXLINE, stdin) != NULL){ // Fgets() = C 내장 함수 (readline)
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    printf("gggg");
    Close(clientfd);
    exit(0);
}

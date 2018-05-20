#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

#define SERVER_PORT 8000
#define MAXLINE 4096

int main(int argc, char* argv[]) {
    struct sockaddr_in server;
    if (argc < 2) {
        printf("./client str\n");
        exit(1);
    }

    // 1.创建一个socket
    int confd = socket(AF_INET, SOCK_STREAM, 0);

    // 2.初始化服务器地址
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    char ipstr[] = "127.0.0.1";
    inet_pton(AF_INET, ipstr, &server.sin_addr.s_addr);
    server.sin_port  = htons(SERVER_PORT);

    // 3.连接服务器
    connect(confd, (struct sockaddr*)&server, sizeof(server));

    // 4.请求服务器处理数据
    write(confd, argv[1], strlen(argv[1]));
    char buf[MAXLINE];
    int len = read(confd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);

    // 5.关闭socket
    close(confd);

	std::cout << std::endl;

    return 0;
}


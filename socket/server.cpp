#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

const int SERVER_PORT = 8000;
const int BUF_SIZE = 4096;
const int ERROR = -1; 

// 消息处理
void process(char*);

int main() {
    // 1.init socket
	int server_socket;
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
		perror("init socket error ");
		exit(1);	
	}

    // 2.bind
    struct sockaddr_in server;
//    bzero(&server, sizeof(server));
	memset(&server, 0, sizeof(server));
    /* 设置地址族协议类型(IPv4), IP, PORT */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVER_PORT);
    if(bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == ERROR) {
		perror("bind socket error ");
		exit(1);
	}

    // 3.listen
    if(listen(server_socket, 128) == ERROR) {
		perror("listen socket error ");
		exit(1);
	}

    while(1) {
        // 4.accept阻塞监听客户端链接请求
    	struct sockaddr_in client;
        socklen_t addrlen = sizeof(client);
        int connect_socket = accept(server_socket, (struct sockaddr*)&client, &addrlen);//返回的是客户端和服务端专用通道的server_socket描述符

        // 输出客户端IP地址和端口号
    	char client_ip[128];
        inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof(client_ip));
//        string client_ip = inet_ntop(AF_INET, &client.sin_addr.s_addr, ipstr, sizeof(ipstr));
		int client_port = ntohs(client.sin_port);
		cout << "Client IP " << client_ip << " Port " << client_port << endl;

        // 和客户端交互数据操作connect_socket
        // 5.处理客户端请求 
    	char buf[BUF_SIZE];
        int len = read(connect_socket, buf, sizeof(buf));

		cout << "Get Message: " << buf << endl;
	
		process(buf);

        write(connect_socket, buf, len);

        close(connect_socket);
    }

    close(server_socket);

    return 0;
}

void process(char* message) {
	for(int i = 0; i < sizeof(message); i++)
		message[i] = toupper(message[i]);
}


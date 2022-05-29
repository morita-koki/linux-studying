#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: $ ./server_socket [port]\n");
        return 1;
    }

    unsigned short port = (unsigned short)atoi(argv[1]);

    int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //socketの生成

    int on = 1;
    int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    if (ret < 0) {
        perror("setsocket");
        return 1;
    }

    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_port = htons(port);
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    fprintf(stderr, "Address=%s, Port=%u\n", inet_ntoa(s_addr.sin_addr), port);

    bind(sfd, (struct sockaddr*)&s_addr, sizeof(s_addr)); //socketのバインド

    listen(sfd, 5); // socketへの新規接続要求を受け付け開始
    fprintf(stderr, "Wainting for connetion...\n");

    struct sockaddr_in c_addr;
    int addr_len = sizeof(struct sockaddr_in);
    int cfd = accept(sfd, (struct sockaddr*)&c_addr, &addr_len); // 接続要求を受け付ける
    fprintf(stderr, "Connected from %s\n", inet_ntoa(c_addr.sin_addr));


    char buf[BUF_SIZE];
    for (;;) {
        memset(buf, 0, BUF_SIZE);
        ret = recv(cfd, buf, BUF_SIZE, 0);
        if (ret == 0 || ret == -1) break;

        fprintf(stderr, "received: %s\n", buf);
        int n = strlen(buf);
        send(cfd, &n, ret, 0);
        ret = strcmp(buf, "exit");
        if (ret == 0) break;
    }

    if (sfd != 1) {
        close(sfd);
    }
    if (cfd != 1) {
        close(cfd);
    }
    return 0;
}
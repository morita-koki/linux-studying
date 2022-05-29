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
    if (argc != 3) {
        fprintf(stderr, "Usage:$ ./client_socket [ip_address] [port]\n");
        return 1;
    }

    char *server_ip = argv[1];
    unsigned short port = (unsigned short)atoi(argv[2]);
    int myfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_port = htons(port);
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr(server_ip);

    fprintf(stderr, "Connecting to %s:\n", server_ip);

    connect(myfd, (struct sockaddr*)&my_addr, sizeof(my_addr));

    for (;;) {
        char word[BUF_SIZE];
        memset(word, 0, BUF_SIZE);
        fprintf(stderr, "> ");
        fgets(word, sizeof(word), stdin);
        word[strlen(word)-1] = '\0';
        send(myfd, word, strlen(word), 0);
        int ret = strcmp(word, "exit");
        if (ret == 0) break;
        
        int n;
        ret = recv(myfd, &n, BUF_SIZE, 0);
        if (ret == 0 || ret == -1) break;
        fprintf(stderr, "from server: %d\n", n);
    }

    if (myfd != -1) {
        close(myfd);
    }
    return 0;
}
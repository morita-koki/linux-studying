#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define BUF_SIZE 256
#define C_MAX 5

void stop(int x);
int sfd = -1;
int socketfds[C_MAX];

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: $ server <port>\n");
        return 1;
    }
    unsigned short port = (unsigned short)atoi(argv[1]);

    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    for (int i = 0; i < C_MAX; ++i) {
        socketfds[i] = -1;
    }

    signal(SIGINT, stop);

    sfd = socket(PF_INET, SOCK_STREAM, 0);

    int on = 1;
    int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    if (ret < 0) {
        perror("setsockopt");
        return 1;
    }

    s_addr.sin_port = htons(port);
    s_addr.sin_family = PF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    fprintf(stderr, "Address=%s, Port=%u\n", inet_ntoa(s_addr.sin_addr), port);

    ret = bind(sfd, (struct sockaddr*)&s_addr, sizeof(s_addr));
    if (ret < 0) {
        perror("bind");
        return 1;
    }

    ret = listen(sfd, 5);
    if (ret < 0) {
        perror("listen");
        return 1;
    }
    fprintf(stderr, "Waiting for connection...\n");

    for (;;) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(sfd, &rfds);
        int fd_max = sfd;
        for (int i = 0; i < C_MAX; ++i) {
            if(socketfds[i] != -1) {
                FD_SET(socketfds[i], &rfds);
                if (socketfds[i] > fd_max) fd_max = socketfds[i];
            }
        }

        struct timeval tm;
        tm.tv_sec = 5;
        tm.tv_usec = 0;
        
        ret = select(fd_max+1, &rfds, NULL, NULL, &tm);
        if (ret < 0) {
            perror("select");
            break; 1;
        }

        ret = FD_ISSET(sfd, &rfds);
        if (ret != 0) {
            fprintf(stderr, "Accept new connection\n");
            for (int i = 0; i < C_MAX; ++i) {
                if (socketfds[i] == -1) {
                    struct sockaddr_in c_addr;
                    int addr_len = sizeof(struct sockaddr_in);
                    socketfds[i] = accept(sfd, (struct sockaddr*)&c_addr, (socklen_t*)&addr_len);
                    fprintf(stderr, "client accepted(%d) from %s\n", i, inet_ntoa(c_addr.sin_addr));
                    fprintf(stderr, "client fd number=%d\n", socketfds[i]);
                    break;
                }
            }
        }

        for (int i = 0; i < C_MAX; ++i) {
            if (socketfds[i] != -1) {
                ret = FD_ISSET(socketfds[i], &rfds);
                if (ret != 0) {
                    char buf[BUF_SIZE];
                    memset(buf, 0, BUF_SIZE);
                    int ret_rcv = recv(socketfds[i], buf, BUF_SIZE, 0);
                    if (ret_rcv > 0) {
                        fprintf(stderr, "recieved: %s\n", buf);
                        int n = strlen(buf);
                        send(socketfds[i], &n, ret_rcv, 0);
                        if (strcmp(buf, "exit") == 0) {
                            close(socketfds[i]);
                            socketfds[i] = -1;
                        }
                    }
                    else {
                        fprintf(stderr, "socket=%d disconnected: \n", socketfds[i]);
                        close(socketfds[i]);
                        socketfds[i] = -1;
                    }
                }
            }
        }
    }
    close(sfd);
}

void stop(int signum) {
    if (sfd != -1) {
        close(sfd);
    }
    for (int i = 0; i < C_MAX; ++i) {
        if (socketfds[i] != -1) {
            close(socketfds[i]);
        }
    }
    exit(1);
}
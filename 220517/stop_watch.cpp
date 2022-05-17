#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <chrono> // C++用

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void stop_watch(int signum);

int main(int argc, char* argv[])
{
    if (argc != 2){
        printf("Usage: ./stop_watch {$number}\n");
        return 1;
    }

    int num_of_sec = atoi(argv[1]);
    if (!num_of_sec) {
        printf("Usage: ./stop_watch {$number}\n");
        return 1;
    }

    signal(SIGALRM, stop_watch);

    printf("Count %d Seconds\n", num_of_sec);
    fflush(stdout);
    usleep(3 * 1000 * 1000);
    printf("Ready");
    fflush(stdout);
    usleep(1 * 1000 * 1000);
    printf(".");
    fflush(stdout);
    usleep(1 * 1000 * 1000);
    printf(".");
    fflush(stdout);
    usleep(1 * 1000 * 1000);
    printf(". ");
    fflush(stdout);
    usleep(1 * 1000 * 1000);
    printf("Go!\n");
    fflush(stdout);

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    alarm(num_of_sec + 10);
    sleep(1);
    printf("1 ");
    fflush(stdout);
    sleep(1);
    printf("2 "); 
    fflush(stdout);
    sleep(1);
    printf("3");
    fflush(stdout);
    sleep(1);
    printf(".");
    fflush(stdout);
    sleep(1);
    printf(". \n");
    fflush(stdout);

    printf("Press Enter to Stop.\n");
    fflush(stdout);
    getchar();
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    printf("your count is %.3lf\n", (end - start) / 1000.);
    return 0;
}

void stop_watch(int signum)
{
    printf("Time Over: count so long.\n");
    exit(0);
}

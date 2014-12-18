#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("begin signal: %u\n", sig);
    sleep(10);
    printf("finish signal: %u\n", sig);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    // sigaddset(&sa.sa_mask, SIGTRAP);
    sa.sa_flags = 0;

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGTRAP, &sa, NULL);
    // signal(SIGTERM, handler);
    // signal(SIGTRAP, handler);

    sigset_t global_set;
    sigemptyset(&global_set);
    // sigaddset(&global_set, SIGTRAP);
    sigprocmask(SIG_SETMASK, &global_set, NULL);

    while (1) {
        sigsuspend(&global_set);
        puts("loop");
    }
    return 0;
}

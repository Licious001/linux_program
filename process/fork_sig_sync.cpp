#include<iostream>
#include<unistd.h>
#include<signal.h>

using namespace std;

#define SYNC_SIG SIGUSR1

static void handler(int sig){}

int main()
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout, NULL);

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SYNC_SIG);
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if(sigaction(SYNC_SIG, &sa, NULL) == -1)
        exit(-1);

    switch(childPid = fork()){
        case 0:
            printf("Child begin to do some work.\n");
            sleep(2);
            printf("Child begin to signal parent.\n");
            kill(getppid(), SYNC_SIG); 
            _exit(EXIT_SUCCESS);
            break;
        default:
            printf("Parent begin to do some work.\n");
            sigemptyset(&emptyMask);
            sigsuspend(&emptyMask);
            printf("Parent recv signal.\n");

            sigprocmask(SIG_SETMASK, &origMask, NULL);
            printf("Parent begin to do some work.\n");
            _exit(EXIT_SUCCESS);
            break;
    }

}
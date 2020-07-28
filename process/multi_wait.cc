#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main(int argc, char* argv[])
{
    int numDead;
    pid_t childPid;
    int j;

    setbuf(stdout, NULL);
    for(j = 1; j < argc; j ++){
        switch(fork()){
            case 0:
                printf("child [%d] started with pid %ld, sleeping %s seconds.\n", j, (long)getpid(), argv[j]);
                sleep(atoi(argv[j]));
                _exit(0);
            default:
                break;
        }
    }
    numDead = 0;
    for(;;){
        childPid = wait(NULL);
        if(childPid == -1 && errno == ECHILD){
            printf("no more children.\n");
            exit(0);
        }
        numDead ++;
        printf("wait returned chiild pid %ld, numDead=%d.\n", (long)childPid, numDead);
    }
}
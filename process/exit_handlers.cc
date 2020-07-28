#include<iostream>
//#include<unistd.h>
#include<stdlib.h>

using namespace std;

static void atexitFunc1(void)
{
    printf("atexit function 1 called.\n");
}

static void atexitFunc2(void)
{
    printf("atexit function 2 called.\n");
}

static void onexitFunc(int status, void *arg)
{
    printf("onexit function 2 called., status=%d, arg=%ld.\n", status, (long)arg);
}

int main()
{
    //on_exit(onexitFunc, (void *)10);
    atexit(atexitFunc1);
    atexit(atexitFunc2);
    atexit(atexitFunc1);
    exit(2);
    return 0;   
}
#include<iostream>
#include<unistd.h>
using namespace std;
static int global = 100;
int main()
{
    int local = 200;
    pid_t childPid = fork();
    switch(childPid){
        case -1:
            cout << "error" << endl;
        break;
        case 0:
        local *= 2;
        global *= 2;
        cout << "child process" << endl;
        break;
        default:
        sleep(5);
        cout << "parent process" << endl;
    }    
    cout << global << "," << local << endl;
    exit(0);

}
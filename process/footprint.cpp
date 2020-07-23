#include<iostream>
#include<unistd.h>
using namespace std;
int func(){
    return 3;
}
int main()
{
   int ret;
   pid_t childPid = fork();
   if (childPid == -1) {
       exit(-1);
   } 

   if(childPid == 0){
       exit(func());
   }

   wait(&ret);
   cout << WEXITSTATUS(ret) << endl;
   exit(0);
}
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


void main(int argc,char *argv){
  pid_t pid;
  char *arr[]={"./b.out","1","2","3","4",NULL};
  
  pid=fork();
  
  if(pid==0){
    execv(arr[0],arr);
  }
  else{
    wait();
  }
}
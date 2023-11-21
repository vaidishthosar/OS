
#include<unistd.h>
#include<semaphore.h>
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t r,w;

int rdct=0;
void *reader(void*arg){
int n= *(int*)arg;
pthread_mutex_lock(&r);
rdct++;
if(rdct==1){
pthread_mutex_lock(&w);
}
pthread_mutex_unlock(&r);
printf("\n reader no=%d",n);
pthread_mutex_lock(&r);
rdct--;
if(rdct==0){
pthread_mutex_unlock(&w);
}
pthread_mutex_unlock(&r);
}

void *writer(void*arg)
{
int n= *(int*)arg;
pthread_mutex_lock(&w);
printf("\n Writer no=%d",n);
pthread_mutex_unlock(&w);
}

void main(){
pthread_t re[10], wr[10];
//int k=1;
int i;
sem_init(&r,0,1);
sem_init(&w,0,1);
for(i=0;i<10;i++){
pthread_create(&re[i],NULL,reader,(void*)&i);
}
for(i=0;i<10;i++){
pthread_create(&wr[i],NULL,writer,(void*)&i
);
}
for(i=0;i<10;i++){
pthread_join(re[i],NULL);
}
for(i=0;i<10;i++){
pthread_join(wr[i],NULL);
}
}






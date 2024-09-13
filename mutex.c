#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int count = 0;
int front = 0, back = 0;
int buffer [BUFFER_SIZE];

pthread_t tid;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void insert(int item){
   while(count==BUFFER_SIZE);
   pthread_mutex_lock(&mutex);

   printf("front: %d inserted: %d\n", front, item);
   buffer[front] = item;
   front = (front+1)%BUFFER_SIZE;
   count++;
   pthread_mutex_unlock(&mutex);
   sleep(1); 
}

int remove_item(){
   while(count==0);
   pthread_mutex_lock(&mutex);
   int item;
   item = buffer[back];
   printf("back: %d removed: %d\n", back, item);
   back = (back+1)%BUFFER_SIZE;
   count--;
   pthread_mutex_unlock(&mutex);
   sleep(1); 
   return item;
}
void * producer(void * param){
   int item;
   while(1){
      item = rand() % BUFFER_SIZE ;
      insert(item);
   }
}
void * consumer(void * param){
   int item;
   while(1){      
   	item = remove_item();
   }
}
int main(int argc, char * argv[])
{
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    int i;
    for (i = 0; i < producers; i++)
       pthread_create(&tid, NULL, producer,NULL);
    for (i = 0; i < consumers; i++)
       pthread_create(&tid, NULL, consumer, NULL); 
    pthread_join(tid,NULL);
   pthread_exit(NULL); // To keep main() from terminating the threads
}
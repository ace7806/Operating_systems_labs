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

sem_t sem;  // To lock the critical code
sem_t inserted, available; // Using semaphores instead of whiles to check whether we can insert into the buffer

void insert(int item){
   sem_wait(&available);
   sem_wait(&sem);   
   buffer[front] = item;
   printf("front: %d inserted: %d\n", front, item);

   front = (front+1)%BUFFER_SIZE;
   count++;
   sem_post(&sem);
   sem_post(&inserted);
   sleep(1); 
}
int remove_item(){
   sem_wait(&inserted);
   sem_wait(&sem);
   int item;
   item = buffer[back];
   printf("back: %d removed: %d\n", back, item);
   back = (back+1)%BUFFER_SIZE;
   count--;
   sem_post(&sem);
   sem_post(&available);
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
    // Initialize the semaphores
    sem_init(&sem, 0, 1);  // Initialize at one to let a thread through
    sem_init(&inserted, 0, 0); // Keeps track of items inserted
    sem_init(&available, 0, BUFFER_SIZE); // Keeps track of any available spots in the buffer (decreases each time)

    for (i = 0; i < producers; i++)
       pthread_create(&tid, NULL, producer,NULL);
    for (i = 0; i < consumers; i++)
       pthread_create(&tid, NULL, consumer, NULL); 
    pthread_join(tid,NULL);
   sem_destroy(&sem);
   sem_destroy(&inserted);
   sem_destroy(&available);
}
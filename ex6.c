#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Using the following rules of the playground:

// Implement using pthreads and pthreads mutex locks.

// Your program should print the kid that is playing, the toy that is using and when the kid finished playing.
// NOTE: if there is an odd number of kids, there will be a kid that will not share.

// NOTE: Code is compiled with gcc on a posix compliant operating system

// To ease coding on a IDE (VSCode) copy all code from the answer box and paste it on IDE text editor. To compile run build task (Terminal>Run Build Task...). To run the code open a new terminal (Terminal>New Terminal) if there isn't one already open and type ./prog <arg> (substitute <arg> to number of kids to test your code).

// The output should look like this: (remember the order of the lines is not enforced)

// Kid 0 is playing with toy 0
// Kid 0 finished playing
// Kid 1 is playing with toy 0
// Kid 1 finished playing

pthread_t *tid;
pthread_mutex_t *toys;

struct kId {
    int id;
    int M;
};

void* kid(void* arg){
    // START ADDING YOUR CODE FROM HERE
    struct kId *currentId= (struct kId *) arg;
    pthread_mutex_t *my_toy;
    int toy_index;
    toy_index = currentId->id/2;
    my_toy = toys + (toy_index);
    pthread_mutex_lock(my_toy);
    printf("Kid %d is playing with toy %d\n", currentId->id, toy_index);
    pthread_mutex_unlock(my_toy);
    printf("Kid %d finished playing\n", currentId->id);
    return NULL;
}

int main(int argc, char *argv[]){
    int i;
    int error;
    int N, M;
    struct kId *tempId;

    if(argc > 2){
        printf("Must supply 1 parameter! (Number of kids)\n");
        return 0;
    }
    N = atoi(argv[1]);
    tid = (pthread_t*)malloc(N*sizeof(pthread_t));
    tempId = (struct kId*)malloc(N*sizeof(struct kId));
    M = N/2;
    if(N%2) M++;
    toys = (pthread_mutex_t*)calloc(M,sizeof(pthread_mutex_t));
    
    for(i = 0; i < M; i++){
        if (pthread_mutex_init(&toys[i], NULL) != 0) {
            printf("\n mutex init has failed\n");
            return 1;
        }
    }
    i = 0;
    while (i < N) {
        tempId[i].id = i;
        tempId[i].M = M;
        error = pthread_create(&(tid[i]), NULL, &kid, &tempId[i]);
        if (error != 0)
            printf("\nThread can't be created : [%d]", error);
        i++;
    }
    i = 0;
    while (i < N) {
        pthread_join(tid[i++], NULL);
    }
  
    free(tid);
    tid = NULL;
    for(i = 0; i < M; i++){
        pthread_mutex_destroy(&toys[i]);
    }
    free(toys);
    toys = NULL;
    free(tempId);
    tempId = NULL;
    return 0;
}
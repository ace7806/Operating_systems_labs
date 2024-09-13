#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// Using the following rules of the construction site:
// N construction workers are taking turns to move stones.
// There are the same amount of stones as construction workers.
// In order to take turns first any worker moves 2 stones.
// Secondly, a worker that already moved 2 stones can only then move a single stone.
// The only stones that worker A can move are stones A-1, A, and A+1. ('A' being a number greater or equal than 0).
// There are not a stone numbered less than 0 and greater than N.
// The worker can move any random stones near them.
// If a worker has not moved any stone they must wait for two available stones to move at the same time.
// If a worker has already moved their first two stones and there isn't any single stone to move they must wait until there is an available stone.
// Any worker finished their job if they completed the steps previously explained.
pthread_t *tid;
pthread_mutex_t *stones;

struct wId {
    int id;
    int M;
};

void* worker(void* arg){
    // YOUR CODE FROM HERE
    struct wId* currentWorker = (struct wId*) arg;
    int A = currentWorker->id;
    int M = currentWorker->M; 
    int condRock = A - 1;
    if (A-1 >= 0) {
        pthread_mutex_lock(stones + A - 1);
    } else if (A + 1 <= M - 1) {
        pthread_mutex_lock(stones + A + 1);
        condRock = A+1;
    }
    pthread_mutex_lock(stones + A);
    printf("Worker %d is moving stones %d and %d\n", A, A, condRock);
    printf("Worker %d finished moving 2 stones\n", A);
    pthread_mutex_unlock(stones + condRock);
    pthread_mutex_unlock(stones + A);

    pthread_mutex_lock(stones + A);
    printf("Worker %d is moving stone %d\n", A, A);
    printf("Worker %d finished moving 1 stone\n", A);
    pthread_mutex_unlock(stones + A);
    // TO HERE
    return NULL;
}

int main(int argc, char *argv[]){
    int i;
    int error;
    int N, M;
    struct wId *tempId;

    if(argc > 2){
        printf("Must supply 1 parameter! (Number of kids)\n");
        return 0;
    }
    N = atoi(argv[1]);
    tid = (pthread_t*)malloc(N*sizeof(pthread_t));
    tempId = (struct wId*)malloc(N*sizeof(struct wId));
    M = N;

    stones = (pthread_mutex_t*)calloc(M,sizeof(pthread_mutex_t));
    
    for(i = 0; i < M; i++){
        if (pthread_mutex_init(&stones[i], NULL) != 0) {
            printf("\n mutex init has failed\n");
            return 1;
        }
    }
    i = 0;
    while (i < N) {
        tempId[i].id = i;
        tempId[i].M = M;
        error = pthread_create(&(tid[i]), NULL, &worker, &tempId[i]);
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
        pthread_mutex_destroy(&stones[i]);
    }
    free(stones);
    stones = NULL;
    free(tempId);
    tempId = NULL;
    return 0;
}
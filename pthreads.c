#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* this data is shared by the thread(s) */
int threads;
unsigned long long iterations;
double * pi;

void * runner(void * param); /* the thread */

int main(int argc, char * argv[]) {
        if (argc != 3) {
            fprintf(stderr, "usage: a.out <iterations> <threads>\n");
            /*exit(1);*/
            return -1;
        }
        if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) {
            fprintf(stderr, "Arguments must be non-negative\n ");
                /*exit(1);*/
                return -1;
            }
        iterations = atoi(argv[1]);
        threads = atoi(argv[2]);
        pi = malloc(sizeof(double)*iterations);
        pthread_t arr_threads[threads];
        for(int i = 0; i<threads; i++){
           
            pthread_create(&arr_threads[i],NULL,runner,i);
        }
        for(int i = 0; i<threads; i++){
            pthread_join(arr_threads[i],NULL);
        }
        double sum = 0;
        for(int i = 0; i<iterations; i++){
            sum+=pi[i];
        }
        sum*=4;

        printf("pi = %.15f\n",sum);
        }
        /**
         * The thread will begin control in this function
         */
        void * runner(void * param) {
            int threadid= param;
            int div = iterations/threads;
            int startpos = div*threadid;
            int endpos = startpos+div;
            for(int i =startpos; i<endpos;i++){
                pi[i]= pow(-1,i)/(2*i+1);
            }

            pthread_exit(0);
        }
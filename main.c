#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 100
#define NUM_SQUARES 10000000

struct pi{
    double sum;
    double step;
    double x;
};
struct pi *init(){
    struct pi *init=malloc(sizeof(struct pi));
    init->sum=0;
    init->step=1/(double)NUM_SQUARES;
    return init;
}
// pi value=3.141592653589793238462643

void *calculate(void *args) {
    struct pi *count=(struct pi*) args;

        for(int i=0;i<NUM_SQUARES/NUM_THREADS;i++){
            count->x+=count->step;
            count->sum+=4.0/(1.0+count->x*count->x);
    }
    count->sum = count->sum*count->step;

    pthread_exit(NULL);
}

int main (int argc, const char * argv[]) {
    
    pthread_t threads[NUM_THREADS];
    time_t start, end;
    int rc;
    double t;
    struct pi *arr[NUM_THREADS];
    start = clock(); // starting timer
    
    for(int i=0;i<NUM_THREADS;i++){
        arr[i]=init();
    }
    
    
    for (int i=0;i<NUM_THREADS;i++) {
        
       arr[i]->x=i*(double)(NUM_SQUARES/NUM_THREADS)*arr[i]->step;
        
        rc = pthread_create(&threads[i],NULL,calculate,(void *)arr[i]);
        
        if (rc) {
            printf("ERROR code coming from pthread_create(): %d\n",rc);
            exit(-1);
        }
    }
    double pi=0;
    // wait for threads to exit
    
    for(int t=0;t<NUM_THREADS;t++) {
        pthread_join( threads[t], NULL);
        pi+=arr[t]->sum;
            }
            end = clock();
            t = (end-start)/CLOCKS_PER_SEC;
            printf("Time = %lf\n", t);
    printf("%f\n",pi);
    return 0;
}


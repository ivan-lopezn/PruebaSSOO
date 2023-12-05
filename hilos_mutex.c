#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int variable=0;
int avgdelay;

pthread_mutex_t mutex;

int get_rand_delay( void) {
    return avgdelay - avgdelay/10 + (rand() % avgdelay) / 5;
}

void * hilo (void *arg) {

    while (1) {

        pthread_mutex_lock(&mutex);
        variable = variable + 1;
        pthread_mutex_unlock(&mutex);

        usleep (get_rand_delay());

        pthread_mutex_lock(&mutex);
        variable = variable - 1;
        pthread_mutex_unlock(&mutex);

        usleep (get_rand_delay());
    }
}

int main( int argc, char* argv[]) {

    int i, nthreads;
    
    avgdelay = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    
    pthread_t th[nthreads];

    pthread_mutex_init(&mutex, NULL);
    
    for(i = 0; i < nthreads; i++) {
        pthread_create(&th[i], NULL, hilo, NULL);
    }
    
    while(1){
        printf("variable=%d\n", variable);
        usleep(500000);
    }

}

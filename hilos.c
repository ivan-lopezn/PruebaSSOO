#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int variable=0;
int avgdelay;

int get_rand_delay( void) {
    return avgdelay - avgdelay/10 + (rand() % avgdelay) / 5;
}

void * hilo (void *arg) {

    while (1) {

        variable = variable + 1;

        usleep (get_rand_delay());

        variable = variable - 1;

        usleep (get_rand_delay());
    }
}

int main( int argc, char* argv[]) {

    int i, nthreads;
    
    avgdelay = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    
    pthread_t th[nthreads];

    for(i = 0; i < nthreads; i++) {
        pthread_create(&th[i], NULL, hilo, NULL);
    }
    
    while(1){
        printf("variable=%d\n", variable);
        usleep(500000);
    }

}

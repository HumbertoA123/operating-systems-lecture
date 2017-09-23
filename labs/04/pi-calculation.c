
/*
https://drive.google.com/open?id=1snkJFSzQeUzWQf8EphietqHZHLjUjk1JsW9B10PJ7R8
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int number, threads;
double *vsum;

void* pie_runner(void* arg)
{
    long j = (long)arg;    

    for(int i = (number/threads)*(j-1); i < ((number/threads)*(j)); i++)
    {

        if(i % 2 == 0){
            vsum[j] += 4.0/((2*j)*(2*j+1)*(2*j+2)); 
                  }
        else{
            vsum[j] -= 4.0/((2*j)*(2*j+1)*(2*j+2));
                  }
    }

    pthread_exit(0);
}

int main(int argc, char **argv)
{

    if(argc != 3) {
        printf("Error: Must send it 2 parameters, you sent %d\n", argc-1);
        exit(1);
    }

    number = atoi(argv[1]);
    threads = atoi(argv[2]); 

    vsum = malloc((threads+1) * sizeof(*vsum));
    if(vsum == NULL) {
        fprintf(stderr, "Memory allocation problem\n");
        exit(1);
    }

    if(number <= threads) {
        printf("Error: Number of terms must be greater then number of threads.\n");
        exit(1);    
    }

    for(int p=1; p<=threads; p++)
    {
        vsum[p] = 0;
    }

    double pie = 3.0;
    pthread_t tids[threads];

    for(long i = 1; i<=threads; i++)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, pie_runner, (void*)i);
    }

    for(int k = 1; k<=threads; k++)
    {
        pthread_join(tids[k], NULL);
    }

    for(int x=1; x<=threads; x++)
    {
        pie += vsum[x];
    }
    

    printf("Pi: %.20f\n", pie);


    free(vsum);
}
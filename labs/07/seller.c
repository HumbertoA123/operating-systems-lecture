#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;
FILE *file;
char buffer[255];
int cookies;
int toSell;

void* transaction() {
    int tmp;

    file = fopen("cookies.txt", "r");
    fscanf(file, "%s", buffer);
    sscanf(buffer, "%d", &cookies);
    fclose(file);

    if (toSell > cookies) {
      printf("No there is not that many cookies, you can sell .. %d\n",cookies);
      return NULL;
    }
    else {
      printf("Ok you can sell them\n");
      file = fopen("cookies.txt", "w+");
      fprintf(file, "%d", cookies - toSell);
      fclose(file);
    }

    return NULL;
}

int main(void) {
    printf("How many cookies do you want to sell?\n");
    scanf("%d", &toSell);
    if(toSell < 0){
        printf("Not a valid amount. \n");
        return 1;
    }
    printf("checking in store ...\n");
    sleep(1);

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_mutex_lock(&lock);
    transaction();
    pthread_mutex_unlock(&lock);

    pthread_mutex_destroy(&lock);
        
    return 0;
}

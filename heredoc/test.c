#include <stdio.h>
#include <pthread.h>

#define NUM_ITERATIONS 100000
pthread_mutex_t x;
pthread_mutex_init(x);
pthread_mutex_lock(&x, NULL);
int counter = 0; 
pthread_mutex_unlock(&x, NULL);

void* increment(void* arg) 
{
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        counter++; 
    }
    return NULL;
}

int main() 
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter); // Expected: 200000
    return 0;
}

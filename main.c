#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *start_routine(void *arg) {
    printf("Thread created\n");
	usleep(2000000);
    return NULL;
}

int main(void) {
    pthread_t thread; // Change to a single pthread_t variable
	pthread_t thread2;

    // Create a thread and check for errors
    if (pthread_create(&thread, NULL, start_routine, NULL) != 0) {
        perror("pthread_create");
        return 1; // Exit with an error code
    }
	if (pthread_create(&thread2, NULL, start_routine, NULL) != 0) {
        perror("pthread_create");
        return 1; // Exit with an error code
    }
    // Wait for the created thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1; // Exit with an error code
    }
    // Wait for the created thread to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("pthread_join");
        return 1; // Exit with an error code
    }
    printf("Main thread: All threads have finished.\n");

    return 0;
}

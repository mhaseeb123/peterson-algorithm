/*
 * Author: Muhammad Haseeb
 * Class: CS5310 | Fall-2017
 * Assignment: Peterson's Algorithm
 * Date: 12/08/2017
 *
 */

 /* Include necessary headers */
#include "PetersonAlgorithm.h"
using namespace std;

/* Global Variables */
PetersonMutex Threads_Lock;
COUNTER counter;

/*
 * FUNCTION: Thread_1_Entry
 * DESCRIPTION: Entry function for Thread 1
 *
 * @params: args: pointer to input arguments
 * @returns: pointer to any results
 */
void *Thread1_Entry(void *arg)
{
    STATUS status = SUCCESS;
    int thread_num = 0;

    while (true)
    {
        /* Acquire the Lock */
        status = PA_Acquire_Mutex(&Threads_Lock, thread_num);

        if (status == SUCCESS)
        {
            /* Check if counter is full */
            if (counter == 30)
            {
                counter = 0;
                printf("\n");
            }
            /* Print c and update counter */
            printf("c");

            counter++;
        }
        else
        {
            printf ("Thread 1: Failed to Acquire the Lock\nExit Thread\n\n");
        }

        status = PA_Release_Mutex(&Threads_Lock, thread_num);

        if (status != SUCCESS)
        {
            printf("Thread 1: Failed to Release the Lock\nExit Thread\n\n");
            break;
        }

    }

    /* No results required */
    return NULL;
}

/*
 * FUNCTION: Thread_2_Entry
 * DESCRIPTION: Entry function for Thread 1
 *
 * @params: args: pointer to input arguments
 * @returns: pointer to any results
 */
void *Thread2_Entry(void *arg)
{
    STATUS status = SUCCESS;
    int thread_num = 1;

    while (true)
    {
        /* Acquire the Lock */
        status = PA_Acquire_Mutex(&Threads_Lock, thread_num);

        if (status == SUCCESS)
        {

            /* Check if counter is full */
            if (counter == 30)
            {
                counter = 0;
                printf("\n");
            }
            /* Print s and update counter */
            printf("s");

            counter++;
        }
        else
        {
            printf("Thread 2: Failed to Acquire the Lock\nExit Thread\n\n");
        }

        status = PA_Release_Mutex(&Threads_Lock, thread_num);

        if (status != SUCCESS)
        {
            printf("Thread 2: Failed to Release the Lock\nExit Thread\n");
            break;
        }

    }

    /* No results required */
    return NULL;
}

/*
 * FUNCTION: main
 * DESCRIPTION: Main function
 *
 * @params: NONE
 * @returns: 0
 */
int main()
{
    STATUS status = SUCCESS;
    void *result_ptr = NULL;

    pthread_t thread1;
    pthread_t thread2;


    printf("Main Task: Creating a MutEx lock\n\n");

    status = PA_Initalize_Mutex(&Threads_Lock);

    /* Initialize Counter to zero */
    counter = 0;

    if (status == SUCCESS)
    {
        printf("Main Task: Creating Thread 1\n");
        status = pthread_create(&thread1, NULL, &Thread1_Entry, NULL);

        if (status == SUCCESS)
        {
            printf("Main Task: Creating Thread 2\n\n");
            status = pthread_create(&thread2, NULL, &Thread2_Entry, NULL);
        }
        else
        {
            printf("Error: Thread 1 Create failed\nABORT!!\n\n");
            status = ERR_THREAD_CREATION_FAILED;
        }

        if (status == SUCCESS)
        {
            /* Sync : Wait for the threads to complete before exiting */
            pthread_join(thread1, &result_ptr);
            pthread_join(thread2, &result_ptr);
            /* All set - Exit now */
            pthread_exit(NULL);
        }
        else
        {
            printf("Error: Thread 2 Create failed\nABORT!!\n\n");
            status = ERR_THREAD_CREATION_FAILED;
        }
    }

    return status;
}

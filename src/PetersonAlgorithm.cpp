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

/*
 * FUNCTION: PA_Acquire_Mutex
 * DESCRIPTION: Acquires the Mutex using Peterson's
 *              Algorithm
 *
 * @params: args: pointer to lock, thread_number
 * @returns: status
 */
STATUS PA_Acquire_Mutex(PetersonMutex *lock, int thread_num)
{
    STATUS status = SUCCESS;

    if (lock == NULL)
    {
        status = ERR_NULL_PARAM;
    }

    if (status == SUCCESS)
    {
        if (thread_num < NUM_THREADS && thread_num >= 0)
        {
            if (lock->useable)
            {
                lock->flag[thread_num] = true;
                lock->turn = thread_num;
                while (lock->flag[NUM_THREADS - 1 - thread_num] && lock->turn == thread_num);
            }
            else
            {
                status = ERR_UNINIT_LOCK;
            }
        }
        else
        {
            status = ERR_THREAD_NUM;
        }
    }

    return status;
}

/*
 * FUNCTION: PA_Release_Mutex
 * DESCRIPTION: Releases the Mutex using Peterson's
 *              Algorithm
 *
 * @params: args: pointer to lock, thread_number
 * @returns: status
 */
STATUS PA_Release_Mutex(PetersonMutex *lock, int thread_num)
{
    STATUS status = SUCCESS;

    if (lock == NULL)
    {
        status = ERR_NULL_PARAM;
    }

    if (status == SUCCESS)
    {
        if (thread_num < NUM_THREADS && thread_num >= 0)
        {
            if (lock->useable)
            {
                lock->flag[thread_num] = false;
            }
            else
            {
                status = ERR_UNINIT_LOCK;
            }
        }
        else
        {
            status = ERR_THREAD_NUM;
        }
    }

    return status;
}

/*
 * FUNCTION: PA_Initialize_Mutex
 * DESCRIPTION: Initializes the Mutex using Peterson's
 *              Algorithm
 *
 * @params: args: pointer to lock
 * @returns: status
 */
STATUS PA_Initalize_Mutex(PetersonMutex *lock)
{
    int idx = 0;
    STATUS status = SUCCESS;

    if (lock == NULL)
    {
        status = ERR_NULL_PARAM;
    }

    if (status == SUCCESS)
    {
        lock ->useable = true;
        lock->turn = -1; /* Reset State */

        for (idx = 0; idx < NUM_THREADS; idx++)
        {
            lock->flag[idx] = false;
        }
    }

    return status;
}

/*
 * FUNCTION: PA_Destroy_Mutex
 * DESCRIPTION: Destroys the Mutex using Peterson's
 *              Algorithm
 *
 * @params: args: pointer to lock
 * @returns: status
 */
STATUS PA_Destroy_Mutex(PetersonMutex *lock)
{
    lock ->useable = false;
    return SUCCESS;
}

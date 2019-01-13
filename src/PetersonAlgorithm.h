/*
 * Author: Muhammad Haseeb
 * Class: CS5310 | Fall-2017
 * Assignment: Peterson's Algorithm
 * Date: 12/08/2017
 *
 */

#ifndef PETERSONALGORITHM_H_
#define PETERSONALGORITHM_H_

 /* Include necessary headers */
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* Status Codes */
#define SUCCESS                          0
#define ERR_NULL_PARAM                  -1000
#define ERR_THREAD_NUM                  -1001
#define ERR_UNINIT_LOCK                 -1002
#define ERR_THREAD_CREATION_FAILED      -1003

/* Macros */
#define NUM_THREADS        2

/* Typedefs */
typedef int STATUS;
typedef unsigned int COUNTER;

/* STRUCT: PetersonMutex
 * DESCRIPTION: Mutex Lock structure that will be
 *              used to implement the Peterson's
 *              Algorithm for mutual exclusion
 *
 * @variables: bool flag[num_threads]
 *             int turn
 */
typedef struct _PetersonMutex
{
    bool flag[NUM_THREADS] = {false};
    int turn = -1; /* Default to -1 */
    bool useable = false;
} PetersonMutex;


/* Prototypes for Peterson's MutEx */
STATUS PA_Acquire_Mutex(PetersonMutex *lock, int thread_num);
STATUS PA_Release_Mutex(PetersonMutex *lock, int thread_num);
STATUS PA_Initalize_Mutex(PetersonMutex *lock);
STATUS PA_Destroy_Mutex(PetersonMutex *lock);

#endif /* PETERSONALGORITHM_H_ */

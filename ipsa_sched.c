/*

Enzo SCAFI :

FINAL ASSIGNMENT: Design an RTOS

*/
#include <stdlib.h>

#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"

/* Priorities at which the tasks are created. */

#define PERIODIC_TASK1_PRIORITY    ( tskIDLE_PRIORITY + 4 ) // first priority
#define PERIODIC_TASK2_PRIORITY    ( tskIDLE_PRIORITY + 3 )
#define PERIODIC_TASK3_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define PERIODIC_TASK4_PRIORITY    ( tskIDLE_PRIORITY + 1 ) // last priority

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */

#define PERIODIC_TASK1_PERIOD_MS   pdMS_TO_TICKS(30UL)   // 30 ms
#define PERIODIC_TASK2_PERIOD_MS   pdMS_TO_TICKS(30UL)   // 30 ms
#define PERIODIC_TASK3_PERIOD_MS   pdMS_TO_TICKS(30UL)   // 30 ms
#define PERIODIC_TASK4_PERIOD_MS   pdMS_TO_TICKS(45UL)   // 45 ms

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 4 )

/* The values for the periodic tasks. */
#define PERIODIC_TASK1_MESSAGE     "Working"
#define PERIODIC_TASK2_TEMP_F      75
#define PERIODIC_TASK3_NUM1        1234567890
#define PERIODIC_TASK3_NUM2        987654321

/* The list for the binary search task. */
#define PERIODIC_TASK4_LIST_SIZE   50
#define PERIODIC_TASK4_SEARCH_ELEM 42

/*-----------------------------------------------------------*/

/*
 * The tasks 
 */
//static void prvQueueReceiveTask( void * pvParameters );
//static void prvQueueSendTask( void * pvParameters );

static void prvPeriodicTask1( void * pvParameters );
static void prvPeriodicTask2( void * pvParameters );
static void prvPeriodicTask3( void * pvParameters );
static void prvPeriodicTask4( void * pvParameters );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

/*-----------------------------------------------------------*/

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void ipsa_sched( void )
{

    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
         * file. */
        xTaskCreate( prvPeriodicTask1,            /* The function that implements the task. */
                        "P1",                     /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                        configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
                        NULL,                     /* The parameter passed to the task - not used in this simple case. */
                        PERIODIC_TASK1_PRIORITY,  /* The priority assigned to the task. */
                        NULL );                   /* The task handle is not required, so NULL is passed. */
                    
        xTaskCreate( prvPeriodicTask2,
                        "P2",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        PERIODIC_TASK2_PRIORITY,
                        NULL );

        xTaskCreate( prvPeriodicTask3,
                        "P3",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        PERIODIC_TASK3_PRIORITY,
                        NULL );

        xTaskCreate( prvPeriodicTask4,
                        "P4",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        PERIODIC_TASK4_PRIORITY,
                        NULL );

        

        if( xTimer != NULL )
        {
            xTimerStart( xTimer, 0 );
        }

        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks	to be created.  See the memory management section on the
     * FreeRTOS web site for more details. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvPeriodicTask1( void * pvParameters )
{
    const TickType_t xPeriod = PERIODIC_TASK1_PERIOD_MS;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Print the message. */
        console_print( PERIODIC_TASK1_MESSAGE );
        console_print( "\n" );

        /* Delay for the specified period. */
        vTaskDelay( xPeriod );
    }
}

/*-----------------------------------------------------------*/

static void prvPeriodicTask2( void * pvParameters )
{
    const TickType_t xPeriod = PERIODIC_TASK2_PERIOD_MS;
    const float fahrenheit = PERIODIC_TASK2_TEMP_F;
    float celsius;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Convert Fahrenheit to Celsius. */
        celsius = (fahrenheit - 32) * 5 / 9;

        /* Print the result. */
        printf( "Temperature in Celsius: %.2f\n", celsius );

        /* Delay for the specified period. */
        vTaskDelay( xPeriod );
    }
}

/*-----------------------------------------------------------*/

static void prvPeriodicTask3( void * pvParameters )
{
    const TickType_t xPeriod = PERIODIC_TASK3_PERIOD_MS;
    const long int num1 = PERIODIC_TASK3_NUM1;
    const long int num2 = PERIODIC_TASK3_NUM2;
    long int result;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Multiply the two numbers. */
        result = num1 * num2;

        /* Print the result. */
        printf( "Multiplication result: %ld\n", result );

        /* Delay for the specified period. */
        vTaskDelay( xPeriod );
    }
}

/*-----------------------------------------------------------*/

static void prvPeriodicTask4( void * pvParameters )
{
    const TickType_t xPeriod = PERIODIC_TASK4_PERIOD_MS;
    const int list[PERIODIC_TASK4_LIST_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    const int searchElem = PERIODIC_TASK4_SEARCH_ELEM;
    int low = 0;
    int high = PERIODIC_TASK4_LIST_SIZE - 1;
    int mid;
    int found = 0;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Binary search algorithm. */
        while (low <= high) {
            mid = (low + high) / 2;

            if (list[mid] == searchElem) {
                found = 1;
                break;
            } else if (list[mid] < searchElem) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        /* Print the search result. */
        if (found) {
            printf("Element %d found at index %d\n", searchElem, mid);
        } else {
            printf("Element %d not found\n", searchElem);
        }

        /* Reset the search variables. */
        low = 0;
        high = PERIODIC_TASK4_LIST_SIZE - 1;
        found = 0;

        /* Delay for the specified period. */
        vTaskDelay( xPeriod );
    }
}

/*-----------------------------------------------------------*/

#include <stdio.h>


/* Priorities at which the tasks are created. */

#define PERIODIC_TASK1_PRIORITY    ( tskIDLE_PRIORITY + 4 )
#define PERIODIC_TASK2_PRIORITY    ( tskIDLE_PRIORITY + 3 )
#define PERIODIC_TASK3_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define PERIODIC_TASK4_PRIORITY    ( tskIDLE_PRIORITY + 1 )


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


static void prvPeriodicTask1(void *pvParameters) {

    (void)pvParameters;

    printf("Message: %s\n", PERIODIC_TASK1_MESSAGE);
}

static void prvPeriodicTask2(void *pvParameters) {
    const float fahrenheit = PERIODIC_TASK2_TEMP_F;
    float celsius;

    (void)pvParameters;

    celsius = (fahrenheit - 32) * 5 / 9;

    printf("Temperature in Celsius: %.2f\n", celsius);

}

static void prvPeriodicTask3(void *pvParameters) {
    const long int num1 = PERIODIC_TASK3_NUM1;
    const long int num2 = PERIODIC_TASK3_NUM2;
    long int result;

    (void)pvParameters;

    result = num1 * num2;

    printf("Multiplication result: %ld\n", result);

}

static void prvPeriodicTask4(void *pvParameters) {
    const int list[PERIODIC_TASK4_LIST_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    const int searchElem = PERIODIC_TASK4_SEARCH_ELEM;
    int low = 0;
    int high = PERIODIC_TASK4_LIST_SIZE - 1;
    int mid;
    int found = 0;

    (void)pvParameters;


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

        if (found) {
            printf("Element %d found at index %d\n", searchElem, mid);
        } else {
            printf("Element %d not found\n", searchElem);
        }

        low = 0;
        high = PERIODIC_TASK4_LIST_SIZE - 1;
        found = 0;


}


int _main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <nombre de 1 à 4>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);

    switch (input) {
        case 1:
            prvPeriodicTask1(NULL);
            break;
        case 2:
            prvPeriodicTask2(NULL);
            break;
        case 3:
            prvPeriodicTask3(NULL);
            break;
        case 4:
            prvPeriodicTask4(NULL);
            break;
        default:
            printf("Entrée invalide\n");
            break;
    }

    return 0;
}

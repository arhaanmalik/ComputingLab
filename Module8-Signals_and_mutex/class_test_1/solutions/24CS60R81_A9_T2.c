#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define UNPROCESSED -1
#define PROCESSED 1
#define MAX_UPDATES 30

int M[100][100];
int A[1000];
int B[1000];
pthread_mutex_t mutex;
pthread_mutex_t matrix_mutex;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_row(int row) {
    for (int j = 0; j < 99; j++) {
        for (int l = j + 1; l < 100; l++) {
            if (M[row][j] > M[row][l]) {
                swap(&M[row][j], &M[row][l]);
            }
        }
    }
}

void* chaos_thread(void* arg) {
    int updates = 0;

    while (updates < MAX_UPDATES) {
        int i = rand() % 100;
        int j = rand() % 100;
        int k = rand() % 1000 + 1;

        pthread_mutex_lock(&matrix_mutex);
        M[i][j] = k;
        printf("Chaos: Updated element at cell [%d][%d] with value %d\n", i, j, k);
        pthread_mutex_unlock(&matrix_mutex);

        pthread_mutex_lock(&mutex);
        A[updates] = i;
        B[updates] = UNPROCESSED;
        pthread_mutex_unlock(&mutex);

        updates++;
        sleep(2);
    }
    printf("CHAOS THREAD ENDS\n");
    return NULL;
}

void* order_thread(void* arg) {
    while (1) {
        int found = 0;

        pthread_mutex_lock(&mutex);

        for (int i = 0; i < MAX_UPDATES; i++) {
            if (B[i] == UNPROCESSED) {
                B[i] = PROCESSED;
                int row = A[i];
                printf("Order: Detected updated element at row %d\n", row);

                pthread_mutex_lock(&matrix_mutex);
                printf("Older row %d: ", row);
                for (int j = 0; j < 100; j++) {
                    printf("%d ", M[row][j]);
                }
                printf("\n");

                sort_row(row);

                printf("New row %d: ", row);
                for (int j = 0; j < 100; j++) {
                    printf("%d ", M[row][j]);
                }
                printf("\n");

                pthread_mutex_unlock(&matrix_mutex);
                found = 1;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (!found) {
            break;
        }
        sleep(1);
    }
    printf("Order Thread Ends\n");
    return NULL;
}

void initialize_matrix(int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = rand() % 1000 + 1;
        }
    }

    printf("Random matrix M of size (%d,%d) is created.\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));
    int m, n;

    printf("Enter the dimensions of the matrix (<= 100 for both): ");
    scanf("%d", &m);
    scanf("%d", &n);

    if (m > 100 || n > 100) {
        printf("Matrix dimensions should not exceed 100.\n");
        return 1;
    }

    initialize_matrix(m, n);

    for (int i = 0; i < MAX_UPDATES; i++) {
        A[i] = UNPROCESSED;
        B[i] = UNPROCESSED;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&matrix_mutex, NULL);

    pthread_t chaos_tid;
    pthread_create(&chaos_tid, NULL, chaos_thread, NULL);

    pthread_t order_tids[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&order_tids[i], NULL, order_thread, NULL);
    }

    pthread_join(chaos_tid, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(order_tids[i], NULL);
    }

    printf("Final Matrix M:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&matrix_mutex);

    return 0;
}

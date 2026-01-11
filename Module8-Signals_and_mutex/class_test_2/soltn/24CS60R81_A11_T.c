#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#define MAX_SIZE 1000
#define UNPROCESSED -1
#define PROCESSED 1
#define NUM_CHAOS 3
#define NUM_ORDER 6

int m, n;
int (*matrix)[MAX_SIZE];
int *A, *B;
sem_t sem_mutex, sem_order;
sem_t row_locks[MAX_SIZE];

void print_matrix() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void chaos_process() {
    srand(time(NULL) ^ getpid());
    for (int count = 0; count < 30; count++) {
        int i = rand() % m;
        int j = rand() % n;
        int new_val = rand() % 1000 + 1;

        sem_wait(&row_locks[i]); // Lock the row
        matrix[i][j] = new_val;
        printf("Chaos: Updated element at cell %d x %d with value %d.\n", i, j, new_val);
        sem_post(&row_locks[i]); // Unlock the row

        sem_wait(&sem_mutex); // Lock the arrays A and B
        A[count] = i;
        B[count] = UNPROCESSED;
        sem_post(&sem_mutex); // Unlock the arrays
        sleep(2);
    }
    printf("CHAOS PROCESS ENDS\n");
    exit(0);
}

void sort_row(int row) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (matrix[row][j] > matrix[row][j + 1]) {
                int temp = matrix[row][j];
                matrix[row][j] = matrix[row][j + 1];
                matrix[row][j + 1] = temp;
            }
        }
    }
}

void order_process() {
    for (int count = 0; count < 30; count++) {
        sem_wait(&sem_order); // Lock the shared arrays A and B
        int row = -1;
        for (int i = 0; i < 30; i++) {
            if (B[i] == UNPROCESSED) {
                B[i] = PROCESSED;
                row = A[i];
                printf("Order: Detected updated element at row %d\n", row);
                break;
            }
        }
        sem_post(&sem_order); // Unlock the shared arrays

        if (row != -1) {
            sem_wait(&row_locks[row]); // Lock the row
            printf("older row %d: ", row);
            for (int j = 0; j < n; j++) printf("%d ", matrix[row][j]);
            printf("\n");

            sort_row(row);

            printf("Order: row %d is sorted now\n", row);
            printf("new row %d: ", row);
            for (int j = 0; j < n; j++) printf("%d ", matrix[row][j]);
            printf("\n");
            sem_post(&row_locks[row]); // Unlock the row
        }
    }
    printf("ORDER PROCESS ENDS\n");
    exit(0);
}

int main() {
    key_t key = IPC_PRIVATE;
    size_t matrix_size = MAX_SIZE * MAX_SIZE * sizeof(int);
    size_t array_size = 2 * MAX_SIZE * sizeof(int);
    int shm_id = shmget(key, matrix_size + array_size, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget failed");
        exit(1);
    }
    int *shared_memory = (int*)shmat(shm_id, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }
    matrix = (int(*)[MAX_SIZE])shared_memory;
    A = shared_memory + (MAX_SIZE * MAX_SIZE);
    B = A + MAX_SIZE;

    printf("Enter the dimensions of the matrix: ");
    scanf("%d %d", &m, &n);
    if (m <= 0 || n <= 0 || m > MAX_SIZE || n > MAX_SIZE) {
        fprintf(stderr, "Invalid matrix dimensions\n");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 1000 + 1;
        }
    }

    printf("Random Matrix M of size (%d,%d) is created in shared memory.\n", m, n);
    print_matrix();

    // Initialize shared arrays
    for (int i = 0; i < MAX_SIZE; i++) A[i] = B[i] = UNPROCESSED;

    sem_init(&sem_mutex, 1, 1);
    sem_init(&sem_order, 1, 1);
    for (int i = 0; i < m; i++) sem_init(&row_locks[i], 1, 1);

    // Spawn chaos processes
    for (int i = 0; i < NUM_CHAOS; i++) {
        if (fork() == 0) {
            printf("I am chaos\n");
            chaos_process();
        }
    }
    // Spawn order processes
    for (int i = 0; i < NUM_ORDER; i++) {
        if (fork() == 0) {
            printf("I am order\n");
            order_process();
        }
    }

    // Wait for all child processes
    for (int i = 0; i < NUM_CHAOS + NUM_ORDER; i++) wait(NULL);
    printf("Final Matrix:\n");
    print_matrix();

    // Cleanup
    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }
    shmctl(shm_id, IPC_RMID, NULL);
    sem_destroy(&sem_mutex);
    sem_destroy(&sem_order);
    for (int i = 0; i < m; i++) sem_destroy(&row_locks[i]);
    return 0;
}


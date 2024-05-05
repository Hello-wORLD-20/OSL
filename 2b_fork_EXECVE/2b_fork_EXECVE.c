
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        int n, i;

        printf("Enter the number of elements: ");
        scanf("%d", &n);

        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Memory allocation failed");
            return 1;
        }

        printf("Enter the elements:\n");
        for (i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed");
            return 1;
        } else if (pid == 0) {
            printf("Array in reverse order: ");
            for (i = n - 1; i >= 0; i--) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        } else {
            bubbleSort(arr, n);
            printf("Sorted array by the parent process: ");
            for (i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            wait(NULL);
        }

        free(arr);
    } else {
        printf("Array in reverse order: ");
        for (int i = argc - 1; i > 0; i--) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Function to sort the tracks according to their distance from the head
void sort_tracks(int tracks[], int n, int head) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (abs(tracks[j] - head) > abs(tracks[j + 1] - head)) {
                int temp = tracks[j];
                tracks[j] = tracks[j + 1];
                tracks[j + 1] = temp;
            }
        }
    }
}

// Function to implement the SSTF algorithm
void SSTF(int tracks[], int n, int head) {
    int seek_count = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    printf("SSTF Disk Scheduling:\n");

    int current = head;
    for (int i = 0; i < n; i++) {
        int min = 9999, min_index;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(tracks[j] - current) < min) {
                min = abs(tracks[j] - current);
                min_index = j;
            }
        }
        visited[min_index] = 1;
        seek_count += min;
        current = tracks[min_index];
        printf("%d -> ", current);
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

// Function to implement the SCAN algorithm
void SCAN(int tracks[], int n, int head, int direction) {
    int seek_count = 0;
    printf("SCAN Disk Scheduling:\n");
    int current = head;
    sort_tracks(tracks, n, head);

    int i;
    for (i = 0; i < n; i++) {
        if (direction == 1 && tracks[i] > head) {
            break;
        }
        if (direction == 0 && tracks[i] < head) {
            break;
        }
    }

    if (direction == 1) {
        for (int j = i; j < n; j++) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
        seek_count += abs(current - 199);
        current = 199;
        printf("%d -> ", current);
        for (int j = i - 1; j >= 0; j--) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
    } else if (direction == 0) {
        for (int j = i - 1; j >= 0; j--) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
        seek_count += abs(current - 0);
        current = 0;
        printf("%d -> ", current);
        for (int j = i; j < n; j++) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

// Function to implement the C-LOOK algorithm
void C_LOOK(int tracks[], int n, int head, int direction) {
    int seek_count = 0;
    printf("C-LOOK Disk Scheduling:\n");
    int current = head;
    sort_tracks(tracks, n, head);

    int i;
    for (i = 0; i < n; i++) {
        if (direction == 1 && tracks[i] > head) {
            break;
        }
        if (direction == 0 && tracks[i] >= head) {
            break;
        }
    }

    if (direction == 1) {
        for (int j = i; j < n; j++) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
        for (int j = 0; j < i; j++) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
    } else if (direction == 0) {
        for (int j = i - 1; j >= 0; j--) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
        for (int j = n - 1; j >= i; j--) {
            seek_count += abs(current - tracks[j]);
            current = tracks[j];
            printf("%d -> ", current);
        }
    }
    printf("\nTotal seek time: %d\n", seek_count);
}

int main() {
    int n, head, direction;
    printf("Enter the number of tracks: ");
    scanf("%d", &n);

    int tracks[n];
    printf("Enter the track positions: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tracks[i]);
    }

    printf("Enter the head position: ");
    scanf("%d", &head);

    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    SSTF(tracks, n, head);

    SCAN(tracks, n, head, direction);

    C_LOOK(tracks, n, head, direction);

    return 0;
}

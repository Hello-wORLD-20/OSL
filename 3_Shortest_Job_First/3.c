
#include <stdio.h>
struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int at;  // Arrival Time
};
void findavgTimeSJF(struct Process proc[], int n) {
    int wt, tat, total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        wt = 0;
        for (int j = 0; j < i; j++) {
            wt += proc[j].bt;
        }
        tat = wt + proc[i].bt;
        total_wt += wt - proc[i].at;
        total_tat += tat - proc[i].at;
    }
    printf("Average waiting time = %f", (float)total_wt / n);
    printf("\nAverage turn-around time = %f", (float)total_tat / n);
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].at);
        proc[i].pid = i + 1;
    }
    findavgTimeSJF(proc, n);
    return 0;
}

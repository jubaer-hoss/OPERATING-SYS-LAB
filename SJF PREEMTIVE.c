#include <stdio.h>

typedef struct {
    int id;      // Process ID
    int burst;   // Total Burst Time
    int remaining; // Remaining Burst Time
    int arrival; // Arrival Time
} Process;

void findWaitingTime(Process proc[], int n, int waitingTime[], int totalTime) {
    int completed = 0, t = 0;
    
    while (completed < n) {
        int idx = -1;
        int min_burst = 9999;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= t && proc[i].remaining > 0 && proc[i].remaining < min_burst) {
                min_burst = proc[i].remaining;
                idx = i;
            }
        }

        if (idx != -1) {
            // Process the selected process
            proc[idx].remaining--;
            t++;
            if (proc[idx].remaining == 0) {
                completed++;
                waitingTime[idx] = t - proc[idx].burst - proc[idx].arrival;
            }
        } else {
            t++; // No process is ready, just advance time
        }
    }
}

void findTurnAroundTime(Process proc[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = proc[i].burst + waitingTime[i];
    }
}

void findavgTime(Process proc[], int n) {
    int waitingTime[n], turnaroundTime[n];
    
    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
    }

    findWaitingTime(proc, n, waitingTime, 0);
    findTurnAroundTime(proc, n, waitingTime, turnaroundTime);

    float totalWait = 0, totalTurn = 0;

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst, waitingTime[i], turnaroundTime[i]);
        totalWait += waitingTime[i];
        totalTurn += turnaroundTime[i];
    }

    printf("Average Waiting Time: %.2f\n", totalWait / n);
    printf("Average Turnaround Time: %.2f\n", totalTurn / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1; // Process IDs from 1 to n
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst);
        printf("Enter arrival time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].arrival);
    }

    findavgTime(proc, n);

    return 0;
}

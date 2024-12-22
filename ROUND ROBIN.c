#include <stdio.h>

typedef struct {
    int id;          // Process ID
    int burst;       // Burst Time
    int remaining;   // Remaining Time
    int wait;        // Waiting Time
    int turn;        // Turnaround Time
} Process;

void calculateTimes(Process proc[], int n, int quantum) {
    int totalTime = 0; // Current time tracker
    int completed = 0; // Number of completed processes

    while (completed < n) {
        int done = 1; // Flag to check if any process has run
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining > 0) {
                done = 0; // At least one process is still running
                if (proc[i].remaining > quantum) {
                    totalTime += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    totalTime += proc[i].remaining;
                    proc[i].wait = totalTime - proc[i].burst; // Waiting time
                    proc[i].turn = totalTime; // Turnaround time
                    proc[i].remaining = 0; // Mark process as completed
                    completed++;
                }
            }
        }
        if (done) {
            totalTime++; // No process is ready, just advance time
        }
    }
}

void printAverageTimes(Process proc[], int n) {
    float totalWait = 0, totalTurn = 0;

    printf("\nProcess ID\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", proc[i].id, proc[i].wait, proc[i].turn);
        totalWait += proc[i].wait;
        totalTurn += proc[i].turn;
    }

    printf("Average Waiting Time: %.2f\n", totalWait / n);
    printf("Average Turnaround Time: %.2f\n", totalTurn / n);
}

// Main function
int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1; // Process IDs from 1 to n
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst);
        proc[i].remaining = proc[i].burst; // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate waiting and turnaround times
    calculateTimes(proc, n, quantum);

    // Print average times
    printAverageTimes(proc, n);

    return 0;
}

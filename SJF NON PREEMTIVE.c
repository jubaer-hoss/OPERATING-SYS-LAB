#include <stdio.h>

typedef struct {
    int id;         
    int burst;     
    int arrival;    
    int wait;       
    int turn;       
} Process;

// Function to sort processes based on arrival time, then burst time
void sortProcesses(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival > proc[j].arrival || 
                (proc[i].arrival == proc[j].arrival && proc[i].burst > proc[j].burst)) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateTimes(Process proc[], int n) {
    int totalTime = 0; 
    int completed = 0; 

    while (completed < n) {
        int idx = -1;
        int min_burst = 9999;

                      // Find the next process to execute
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= totalTime && proc[i].burst > 0) {
                if (proc[i].burst < min_burst) {
                    min_burst = proc[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
                     // Process the selected process
            totalTime += proc[idx].burst;
            proc[idx].wait = totalTime - proc[idx].arrival - proc[idx].burst; 
            proc[idx].turn = totalTime - proc[idx].arrival; 
            proc[idx].burst = 0; 
            completed++;
        } else {
            totalTime++; 
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

    sortProcesses(proc, n);

    calculateTimes(proc, n);

    printAverageTimes(proc, n);

    return 0;
}

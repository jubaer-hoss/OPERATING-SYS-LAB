
#include <stdio.h>

int main() {
    int n; 
    int pid[20]; 
    int bt[20]; 
    int wt[20]; 
    int tat[20]; 
    float total_wt = 0, total_tat = 0; 

  
    printf("Enter the number of processes: ");
    scanf("%d", &n);

  
    printf("Enter process IDs: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pid[i]);
    }

    
    printf("Enter burst times for each process: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }


    wt[0] = 0; 
    for(int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    
    for(int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", pid[i], bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

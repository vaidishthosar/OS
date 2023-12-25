#include<stdio.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completed;
};

void SJF(struct Process processes[], int n) {
    int time = 0;
    int completed = 0;
    int shortest = -1;
    int min_burst = __INT_MAX__;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time < min_burst && processes[i].remaining_time > 0) {
                min_burst = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            printf("No process available at time %d\n", time);
            time++;
            continue;
        }

        processes[shortest].remaining_time--;
        min_burst = processes[shortest].remaining_time;

        if (min_burst == 0) {
            min_burst = __INT_MAX__;
            completed++;
            processes[shortest].completed = time + 1;
        }

        time++;
    }

    printf("\nPID\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    int total_turnaround = 0, total_waiting = 0;
    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].completed - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;
        total_turnaround += turnaround_time;
        total_waiting += waiting_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].completed, turnaround_time, waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);
}

void RoundRobin(struct Process processes[], int n, int time_quantum) {
    int time = 0;
    int completed = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completed = time;
                    completed++;
                }
            }
        }
    }

    printf("\nPID\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    int total_turnaround = 0, total_waiting = 0;
    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].completed - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;
        total_turnaround += turnaround_time;
        total_waiting += waiting_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].completed, turnaround_time, waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter the burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    SJF(processes, n);

    return 0;
}

#include <stdio.h>

#define NUM_PROCESSES 3
#define TIME_QUANTUM 4

typedef struct {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

Process processes[NUM_PROCESSES] = {
    {0, 5, 5, 0, 0}, // P1
    {1, 3, 3, 0, 0}, // P2
    {2, 6, 6, 0, 0}  // P3
};

void round_robin_scheduling() {
    int current_time = 0;
    int i, j;
    int completed_processes = 0;

    while (completed_processes < NUM_PROCESSES) {
        for (i = 0; i < NUM_PROCESSES; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                int time_slice = TIME_QUANTUM;
                if (processes[i].remaining_time < TIME_QUANTUM) {
                    time_slice = processes[i].remaining_time;
                }
                processes[i].remaining_time -= time_slice;
                current_time += time_slice;
                printf("Process %c executes for %d units at time %d\n", '1' + i, time_slice, current_time - time_slice);

                if (processes[i].remaining_time == 0) {
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed_processes++;
                }
            }
        }
    }

    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        printf("P%d\t%d\t\t%d\n", i + 1, processes[i].turnaround_time, processes[i].waiting_time);
    }

    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;
    for (i = 0; i < NUM_PROCESSES; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= NUM_PROCESSES;
    avg_waiting_time /= NUM_PROCESSES;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    round_robin_scheduling();
    return 0;
}

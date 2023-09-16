#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid;
  int arrival_time;
  int burst_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
} Process;

void sort_processes_by_arrival_time(Process *processes, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (processes[i].arrival_time > processes[j].arrival_time) {
        Process temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
}

void find_waiting_time(Process *processes, int n) {
  for (int i = 1; i < n; i++) {
    processes[i].waiting_time = processes[i - 1].completion_time - processes[i].arrival_time;
  }
}

void find_turnaround_time(Process *processes, int n) {
  for (int i = 0; i < n; i++) {
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
  }
}

void shortest_job_first(Process *processes, int n) {
  sort_processes_by_arrival_time(processes, n);
  int current_time = 0;
  for (int i = 0; i < n; i++) {
    processes[i].completion_time = current_time + processes[i].burst_time;
    current_time += processes[i].burst_time;
  }
}

void main() {
  Process processes[10];

  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("Enter the arrival time and burst time of process %d: ", i + 1);
    scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
  }

  shortest_job_first(processes, n);

  find_waiting_time(processes, n);
  find_turnaround_time(processes, n);

  printf("Process ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
  }
}

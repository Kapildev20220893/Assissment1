#include <stdio.h>
#include <stdlib.h>

typedef struct process {
  int pid;
  int burst_time;
  int priority;
  int waiting_time;
  int turnaround_time;
} Process;

void priority_scheduling(Process *processes, int n) {
  // Sort the processes by priority in descending order.
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (processes[i].priority < processes[j].priority) {
        Process temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }

  // Calculate the waiting and turnaround times for each process.
  int current_time = 0;
  for (int i = 0; i < n; i++) {
    processes[i].waiting_time = current_time - processes[i].arrival_time;
    current_time += processes[i].burst_time;
    processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
  }
}

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  Process *processes = (Process *)malloc(sizeof(Process) * n);

  for (int i = 0; i < n; i++) {
    printf("Enter the burst time and priority of process %d: ", i + 1);
    scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
    processes[i].pid = i + 1;
    processes[i].arrival_time = 0;
  }

  priority_scheduling(processes, n);

  printf("Process ID | Burst time | Priority | Waiting time | Turnaround time\n");
  printf("-----------|------------|-----------|------------|------------\n");
  for (int i = 0; i < n; i++) {
    printf("%-10d | %-10d | %-10d | %-10d | %-10d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
  }

  free(processes);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct process {
  int pid;
  int burst_time;
  int priority;
  int waiting_time;
  int turnaround_time;
} Process;

void round_robin_scheduling(Process *processes, int n, int quantum) {
  // Create a queue to store the processes.
  Queue *queue = create_queue();

  // Add all the processes to the queue.
  for (int i = 0; i < n; i++) {
    enqueue(queue, &processes[i]);
  }

  // Simulate the round robin scheduling algorithm.
  int current_time = 0;
  while (!is_empty(queue)) {
    // Get the next process from the queue.
    Process *process = dequeue(queue);

    // If the process has more burst time remaining, execute it for the quantum.
    if (process->burst_time > quantum) {
      process->burst_time -= quantum;
      current_time += quantum;
      enqueue(queue, process);
    } else {
      // The process has completed execution.
      current_time += process->burst_time;
      process->turnaround_time = current_time - process->arrival_time;
      process->waiting_time = process->turnaround_time - process->burst_time;
    }
  }
}

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  int quantum;
  printf("Enter the quantum: ");
  scanf("%d", &quantum);

  Process *processes = (Process *)malloc(sizeof(Process) * n);

  for (int i = 0; i < n; i++) {
    printf("Enter the burst time and priority of process %d: ", i + 1);
    scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
    processes[i].pid = i + 1;
    processes[i].arrival_time = 0;
  }

  round_robin_scheduling(processes, n, quantum);

  printf("Process ID | Burst time | Priority | Waiting time | Turnaround time\n");
  printf("-----------|------------|-----------|------------|------------\n");
  for (int i = 0; i < n; i++) {
    printf("%-10d | %-10d | %-10d | %-10d | %-10d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
  }

  free(processes);

  return 0;
}

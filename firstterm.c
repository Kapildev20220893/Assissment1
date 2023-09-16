#include <stdio.h>

// Structure to represent a process
typedef struct {
  int pid; // Process ID
  int bt; // Burst time
  int wt; // Waiting time
  int tat; // Turnaround time
} Process;

// Function to calculate the waiting time for each process
void calculateWaitingTime(Process p[], int n) {
  p[0].wt = 0; // Waiting time for the first process is 0
  for (int i = 1; i < n; i++) {
    p[i].wt = p[i - 1].wt + p[i - 1].bt;
  }
}

// Function to calculate the turnaround time for each process
void calculateTurnaroundTime(Process p[], int n) {
  for (int i = 0; i < n; i++) {
    p[i].tat = p[i].wt + p[i].bt;
  }
}

// Function to print the results
void printResults(Process p[], int n) {
  printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
  }
}

int main() {
  int n; // Number of processes
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  // Create an array of processes
  Process p[n];
  for (int i = 0; i < n; i++) {
    printf("Enter the burst time for process %d: ", i + 1);
    scanf("%d", &p[i].bt);
    p[i].pid = i + 1;
  }

  // Calculate the waiting time and turnaround time for each process
  calculateWaitingTime(p, n);
  calculateTurnaroundTime(p, n);

  // Print the results
  printResults(p, n);

  return 0;
}

#include <stdio.h>

struct Definitions{
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
	int done;
};

// bubble sorting by arrival time
void sortByArrival(struct Definitions p[], int n) {
    int i, j;
    struct Definitions temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// FCFS Scheduling
void fcfs(struct Definitions p[], int n) {
    int i;
    int current_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    sortByArrival(p, n);

    printf("\n=== First Come First Served (FCFS) ===\n");
    printf("Gantt Chart: |");

    for (i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;

        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        current_time += p[i].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;

        printf(" P%d |", p[i].pid);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }

    printf("\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

// Shortest Job First (Non-preemptive)
void sjf(struct Definitions p[], int n) {
    int done = 0, current_time = 0;
    int i, idx;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (i = 0; i < n; i++)
        p[i].done = 0;

    printf("\n=== Shortest Job First (SJF) ===\n");
    printf("Gantt Chart: |");

    while (done != n) {
        idx = -1;
        int min_bt = 9999;

        // find process with smallest burst time among arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].done == 0) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_bt) {
                    // if burst times equal, choose earlier arrival
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            // execute process
            p[idx].waiting_time = current_time - p[idx].arrival_time;
            if (p[idx].waiting_time < 0)
                p[idx].waiting_time = 0;

            p[idx].response_time = p[idx].waiting_time;
            current_time += p[idx].burst_time;
            p[idx].turnaround_time = p[idx].waiting_time + p[idx].burst_time;
            p[idx].done = 1;
            done++;

            printf(" P%d |", p[idx].pid);

            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
            total_rt += p[idx].response_time;
        } else {
            // no process has arrived yet
            current_time++;
        }
    }

    printf("\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

int main() {
    int n, i;
    struct Definitions p[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    // copy array for both algorithms for results not to overlap
    struct Definitions p_fcfs[20], p_sjf[20];
    for (i = 0; i < n; i++) {
        p_fcfs[i] = p[i];
        p_sjf[i] = p[i];
    }

    fcfs(p_fcfs, n);
    sjf(p_sjf, n);

    return 0;
}


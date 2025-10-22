# OS_Fall25_Homework7
This repo contains program files for the 7th homework assignment. 

## Description
This program is a simple CPU Process Scheduling Simulator written in C, demonstrates how two classic scheduling algorithms, FCFS and SJF, work by simulating their behavior using user input.

The simulator calculates and displays: Waiting Time (WT), Turnaround Time (TAT), Response Time (RT), Gantt Chart of execution order, Average waiting, turnaround, and response times. It doesn't create real processes, instead, it performs a logical simulation based on the input.

## How to Compile and Run

1. Navigate to the directory containing the source file:
cd path/to/directory

2. Compile the program using GCC:
gcc scheduling_simulator.c -o scheduler

3. Run the executable:
./scheduler

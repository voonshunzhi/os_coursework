#include<stdio.h>

int find_turnaround(int arrival_time, int completion);
int find_waiting_time(int turnaround, int burst_time);

int main()
{
    int number_of_processes, total_time, remain, completed = 0, id = 0;
    int total_wait_time = 0,total_turnaround_time = 0;
    int ids[10][10], fcfs_bt_queue[10];

    int arrival_time[] = {0,10,20,30,40};
    int burst_time[] = {5,34,43,67,81};
    int remaining_time[10], arrival_time_copy[10];
    int time_quantum;
    int fcfs_waiting_time = 0;
    int fcfs_turnaround_time = 0;

    int length = sizeof(arrival_time) / sizeof(arrival_time[0]);
    number_of_processes = length;

    printf("Enter a suitable time quantum :");
    scanf("%d",&time_quantum);


  for(int i = 0; i < length; i++)
    {
        remaining_time[i] = burst_time[i];
    }

    printf(" _________________________________________________________________________________\n");
    printf("|           |                |                |                |                  |\n");
    printf("|%s |%14s  |%13s   |%14s  |%17s |\n"," Processes","Arrival Time","Burst time","Waiting time","Turn around time");
    printf("|___________|________________|________________|________________|__________________|\n");
    printf("|           |                |                |                |                  |\n");

  total_time = arrival_time[0];

  for(int i = 0, flag = 0, waiting_time = 0; i < number_of_processes; i++) {

    ids[i+1][0] = arrival_time[i];
    ids[i+1][1] = burst_time[i];

    if(remaining_time[i] <= time_quantum)
    {
      total_time += remaining_time[i];
      fcfs_bt_queue[i] = 0;
       int turnaround = find_turnaround(arrival_time[i], total_time);
      int waiting = find_waiting_time(turnaround, burst_time[i]);
      ids[i+1][2] = waiting + waiting_time;
      ids[i+1][3] = turnaround;
      waiting_time += remaining_time[i];
    }
    else 
    {
      int remaining = remaining_time[i] - time_quantum;
      total_time += time_quantum;
      fcfs_bt_queue[i] = remaining;
    }

    if(arrival_time[i + 1] >= total_time) 
    {
      total_time += arrival_time[i+1] - total_time;
    }
  }

  for(int i = 0, waiting_time = 0; i < number_of_processes; i++) 
  {
    if(fcfs_bt_queue[i] > 0) 
    {
      total_time += fcfs_bt_queue[i];
      ids[i+1][2] = total_time - arrival_time[i] - remaining_time[i];
      ids[i+1][3] = total_time - arrival_time[i];
    }
  }

  for(int i = 1; i <= number_of_processes; i++) {
      printf("|     %d     |",i);
      printf("%9d       |", ids[i][0]);
      printf("%10d      |", ids[i][1]);
      printf("%10d      |",ids[i][2]);
      printf("%10d        |\n",ids[i][3]);
  }

  printf("|___________|________________|________________|________________|__________________|\n");

  printf("\nAverage Waiting Time= %f", (float)total_wait_time/number_of_processes);
  printf("\nAvg Turnaround Time = %f", (float)total_turnaround_time/number_of_processes);
  printf("\nThroughput = %f\n", (float) number_of_processes / total_time);

  return 0;
}

int find_turnaround(int arrival_time, int completion){
    int turnaround = completion - arrival_time;
    return turnaround;
}

int find_waiting_time(int turnaround, int burst_time){
    int waiting_time = (turnaround - burst_time);
    return waiting_time;
}

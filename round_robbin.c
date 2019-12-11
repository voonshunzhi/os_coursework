#include<stdio.h>
#include <stdlib.h>

int find_turnaround(int arrival_time, int completion);
int find_waiting_time(int turnaround, int burst_time);
void copyArray(int a[],int burstTime[],int noOfProcesses);

int main()
{
    int choice;
    int count, number_of_processes, total_time, remain, completed = 0, id=0;
    int total_wait_time = 0,total_turnaround_time = 0;
    int ids[10][10];

    int arrival_time[] = {5,16,25,34,44};
    int ascendingBurstTime[] = {9,25,36,42,100};
    int descendingBurstTime[] = {55,42,36,25,18};
    int remaining_time[10];
    int time_quantum;

    int length = sizeof(arrival_time) / sizeof(arrival_time[0]);
    number_of_processes = length;
    remain=number_of_processes;
    int burst_time[number_of_processes];

    printf("Press 1 for ascending workload or Press 2 for descending workload\n");
    printf("Enter your choice :");
    scanf("%d",&choice);

    if(choice == 1)
    {
        //assign burst time with ascending order workload
        copyArray(ascendingBurstTime,burst_time,number_of_processes);
    }
    else
    {
        //assign burst time with descending order workload
        copyArray(descendingBurstTime,burst_time,number_of_processes);
    }

    printf("Enter a suitable time quantum :");
    scanf("%d",&time_quantum);

  for(int i = 0; i < length; i++)
    {
        // Remainig time is a copy of burst time to keep burst time intact
        remaining_time[i] = burst_time[i];
    }

    printf(" _________________________________________________________________________________\n");
    printf("|           |                |                |                |                  |\n");
    printf("|%s |%14s  |%13s   |%14s  |%17s |\n"," Processes","Arrival Time","Burst time","Waiting time","Turn around time");
    printf("|___________|________________|________________|________________|__________________|\n");
    printf("|           |                |                |                |                  |\n");


  for(total_time= arrival_time[0], count=0; remain!= 0;)
  {
    // if remaining_time[count] == 0; meaning done
    if(remaining_time[count] <= time_quantum && remaining_time[count] > 0)
    {   total_time += remaining_time[count];
      remaining_time[count]=0;
      completed = 1;
    }
    else if(remaining_time[count]>0)
    {
      remaining_time[count]-=time_quantum;
      total_time+=time_quantum;
    }
    if(remaining_time[count]==0 && completed == 1)
    {
      remain--;
      int turnaround = find_turnaround(arrival_time[count], total_time);
      int waiting = find_waiting_time(turnaround, burst_time[count]);
      total_wait_time += waiting;
      total_turnaround_time += turnaround;
      ids[count+1][0] = arrival_time[count];
      ids[count+1][1] = burst_time[count];
      ids[count+1][2] = waiting;
      ids[count+1][3] = turnaround;
      completed = 0;
    }
    
    
    if(count == number_of_processes-1)
      //If reach the end of array reset to 0
      count=0;
    else if(arrival_time[count+1] <= total_time)
      count++;
      
    else if(arrival_time[count+1] > total_time) {
        // if next process havent arrive yet, add the difference find_turnaround
        total_time += arrival_time[count+1] - total_time;
    }
    
    else
      // if next element havent arrived yet go back to first element and run again
      count=0;
      
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

//function to copy elements of an array to another array
void copyArray(int a[],int burstTime[],int number_of_processes)
{
    for (int i=0 ;i<number_of_processes ;i++)
    {
        burstTime[i] = a[i];
    }
}

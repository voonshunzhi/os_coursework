#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int find_turnaround(int arrival_time, int completion);
int find_waiting_time(int turnaround, int burst_time);
void print_output(int turnaround, int waiting_time, int process);
bool check_completion(int remaining_burst_array[], int size);
bool check_arrival(int arrival_array[], int current_time, int i, int size);

int main(){
    
    // Declaring variables
    bool completed = false;
    int time_quantum = 50, tracking_counter = 0;
    int burst_time, arrival_time, waiting_time, turnaround_time;

    //Arrays to store different values
    int arrival_array_asc[100000] = {0,10,20,30,40,50};

    // Ascending and Descending order dummy data
    int burst_array_asc[] = {10,20,30,40,50,60};

    // To find the number of items in the array
    int input_arraySize = sizeof(burst_array_asc)/ sizeof(burst_array_asc[0]);

    // Copy arrival array
    int copy_arrival_array[100000];
    int copy_burst_array[100000];
    int process_ids[100000];

    for(int i = 0; i < input_arraySize; i++) {
      copy_arrival_array[i] = arrival_array_asc[i];
      copy_burst_array[i] = burst_array_asc[i];
      process_ids[i] = i+1;
    }

        int count = 0;
        int num_of_process_pending = 0;
        int dynamic_array_length = 0;
        int exceed[100000];
    

        for(int i= 0;i<input_arraySize + dynamic_array_length; i++){
            int remaining_burst = 0; 
            int n = 0;

            if(burst_array_asc[i] > 0) {
              if (burst_array_asc[i] > time_quantum){
                remaining_burst = burst_array_asc[i] - time_quantum;
                tracking_counter += time_quantum;
                num_of_process_pending++;
                dynamic_array_length++;
                
                for(int j = i+1; j < input_arraySize; j++){
                  if(tracking_counter > arrival_array_asc[j] && arrival_array_asc[j] != 0) {
                    n++;
                  }
                }


                int c =  i + n + num_of_process_pending;

                for(int i = (input_arraySize - 1) + dynamic_array_length; c < i; i--) {
                  burst_array_asc[i] = burst_array_asc[i-1];
                  copy_arrival_array[i] = copy_arrival_array[i-1];
                  copy_burst_array[i] = copy_burst_array[i-1];
                  process_ids[i] =  process_ids[i-1];
                }

                burst_array_asc[c] = remaining_burst;
                copy_arrival_array[c] = copy_arrival_array[i];
                copy_burst_array[c] = copy_burst_array[i];
                 process_ids[c] =  process_ids[i];
                exceed[c] = true;
                burst_array_asc[i] = 0;

              }

            // Burst time is within time quantum
              else {
                tracking_counter += burst_array_asc[i];
                burst_array_asc[i] = 0;
                if(exceed[i] == true) {
                  num_of_process_pending--;
                }

                int turnaround = find_turnaround(copy_arrival_array[i], tracking_counter);

                int waiting = find_waiting_time(turnaround, copy_burst_array[i]);

                print_output(turnaround, waiting,  process_ids[i]);
              }
            }
           }
}

int find_turnaround(int arrival_time, int completion){
    int turnaround = completion - arrival_time;

    return turnaround;
}

int find_waiting_time(int turnaround, int burst_time){
    int waiting_time = (turnaround - burst_time);

    return waiting_time;
}

void print_output(int turnaround, int waiting_time, int process){
    printf("Process %d\n", process);
    printf("Turnaround time is: %d\nWaiting time is: %d\n\n", turnaround, waiting_time); 
}


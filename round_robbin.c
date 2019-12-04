#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

float find_turnaround(int arrival_time, int completion);
float find_waiting_time(int turnaround, int burst_time);
const char *print_output(int turnaround, int waiting_time, int process);
bool check_completion(int remaining_burst_array[], int size);
bool check_arrival(int arrival_array[], int current_time, int i, int size);

int main(){
    
    // Declaring variables
    bool completed = false;
    int time_quantum = 5, tracking_counter = 0;
    int burst_time, arrival_time, waiting_time, turnaround_time;

    //Arrays to store different values
    int arrival_array_asc[100] = {0,3,4,8};

    // Ascending and Descending order dummy data
    int burst_array_asc[] = {6,7,8,9};

    // To find the number of items in the array
    int input_arraySize = sizeof(burst_array_asc)/ sizeof(burst_array_asc[0]);

    // printf("The size of array is %d\n", input_arraySize);

    // While the array has not finished traversing, continue the loop
    // Currently an infinite loop because havent changed flag
    //while(!completed){
        // Variable to track arrival time count

    // Copy arrival array
    int copy_arrival_array[100];

    for(int i = 0; i < input_arraySize; i++) {
      copy_arrival_array[i] = arrival_array_asc[i];
    }

        int count = 0;
        int num_of_process_pending = 0;
        int dynamic_array_length = 0;
        int exceed[1000];
    

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

                printf("The value of n is %d at %d iteration \n", n, i);
                printf("The total time taken is %d \n", tracking_counter);

                int c =  i + n + num_of_process_pending;

                for(int i = (input_arraySize - 1) + dynamic_array_length; c < i; i--) {
                  burst_array_asc[i] = burst_array_asc[i-1];
                  copy_arrival_array[i] = copy_arrival_array[i-1];
                }

                burst_array_asc[c] = remaining_burst;
                copy_arrival_array[c] = copy_arrival_array[i];
                exceed[c] = true;
                burst_array_asc[i] = 0;

                  for(int i = 0; i < input_arraySize + dynamic_array_length ; i ++) {
                printf("\n The values in array are %d \n", burst_array_asc[i]);
              }
              }

            // Burst time is within time quantum
              else {
                tracking_counter += burst_array_asc[i];
                burst_array_asc[i] = 0;
                printf("The value of n is %d at %d iteration \n", n, i);
                printf("The total time taken is %d \n", tracking_counter);
                for(int i = 0; i < input_arraySize + dynamic_array_length ; i ++) {
                printf("\n The values in array are %d \n", burst_array_asc[i]);
                }
                if(exceed[i] == true) {
                  num_of_process_pending--;
                }

                printf("The total time taken is %d \n", tracking_counter);
                printf("The arrival time is %d \n", copy_arrival_array[i]);
                printf("The waiting time is %d \n", tracking_counter - copy_arrival_array[i]);
              }
            }

            printf("==Done==#%d\n",i);


              }


        //printf("Total time is %d\n",tracking_counter);
        // completed = check_completion(burst_array_asc, input_arraySize);
        completed = true;
    //}
}

float find_turnaround(int arrival_time, int completion){
    int turnaround = completion - arrival_time;

    return turnaround;
}

float find_waiting_time(int turnaround, int burst_time){
    int waiting_time = -(turnaround - burst_time);

    return waiting_time;
}

const char *print_output(int turnaround, int waiting_time, int process){
    printf("Process %d\n", process);
    printf("Turnaround time is: %d\nWaiting time is: %d\n\n", turnaround, waiting_time); 

}

bool check_completion(int burst_array[], int size){
    for(int i = 0; i < size; i++){
        if (burst_array[i] != 0){
            return false;
        }
        else{
            return true;
        }
    }
}

bool check_arrival(int arrival_array[], int current_time, int i, int size){
    for (; i < size; i++){
        if (arrival_array[i] > current_time) {
            return true;
        }
        else{
            return false;
        }
    }
    // Return number of processes arrived
}

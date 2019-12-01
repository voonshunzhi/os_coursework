#include <stdio.h>

int main(void) {

  // n is number of processes, exeTime is array to store 
  int n, exeTime[100], wTime = 0, taTime = 0;
  float awTime = 0, ataTime = 0, twTime = 0, ttaTime = 0;
  int i;

  printf("The number of processes: ");
  scanf("%d", &n);

  for(i = 0; i < n; i++) {
    printf("Please enter exec time for processes number %d: ", i+1);
    scanf("%d", &exeTime[i]);
  }

  printf("Pid \t\t BT \t\t WT \t\t taTime");

  for(i = 0; i < n; i++) {
    taTime = exeTime[0] + wTime;
    printf("\n %d \t\t %d \t\t %d \t\t %d", i + 1, exeTime[i], wTime, taTime);
    wTime += exeTime[i];
    twTime += wTime;
    ttaTime += taTime;
  }

  awTime = twTime / n;
  ataTime = ttaTime / n;
  printf("\nAverage Waiting Time: %f ", awTime);
  printf("\nAverage Turnaround Time: %f ", ataTime);
}

#include <stdio.h>
#include <stdlib.h>
#include "math.h"


 typedef struct {
  int pid; // process ID
  int at; // arrival time
  int bt; // burst time
 } process;

int find_next_for_execution(process *arr, int total_elements, int current_time)
{
    int min = pow(2, 10), min_index;

    for(int i = 0 ; i < total_elements ; i++)
    {
        if(arr[i].bt != 0 && arr[i].at <= current_time)
        {
            if(min > arr[i].bt)
            {
                min = arr[i].bt;
                min_index = i;
            }
        }
    }

    return min_index;
}


 int main() {

  /* read in data - DO NOT EDIT (START) */
  int n;
  int quantum;
  scanf("%d", &n);
  scanf("%d", &quantum);
  process *arr;
  arr = malloc(n * sizeof(process));
  for (int i = 0; i < n ; ++i) {
    scanf("%d", &arr[i].pid);
    scanf("%d", &arr[i].at);
    scanf("%d", &arr[i].bt);
  }
  /* read in data - DO NOT EDIT (END) */

   int current_time = 0,burst_time, for_execution = 0, processes_finished = 0;

   while(1)
   {
       burst_time = arr[for_execution].bt;
       for(int i = 0 ;i < burst_time ;i++)
       {
           printf("%d\n",arr[for_execution].pid);
       }
       current_time += burst_time;
       arr[for_execution].bt = 0;
       for_execution = find_next_for_execution(arr, n, current_time);
       processes_finished ++;

       if(processes_finished == n)
       {
           break;
       }

   }

  return 0; /* DO NOT EDIT THIS LINE */
 }

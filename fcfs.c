#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid; // process ID
  int at; // arrival time
  int bt; // burst time
} process;


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

  /**
  Οι διεργασίες δίνονται με την σειρά άφιξης τους, αρα χρειαζόμαστε 2 loops.
  **/
  for(int i = 0 ; i < n ;i++)
  {
    for(int j = 0 ; j < arr[i].bt ;j++)
      {
         printf("%d\n", arr[i].pid);
      }
  }
  return 0; /* DO NOT EDIT THIS LINE */
}

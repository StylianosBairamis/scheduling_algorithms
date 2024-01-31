#include <stdio.h>
#include <stdlib.h>
#include "math.h"

typedef struct {
    int pid; // process ID
    int at; // arrival time
    int bt; // burst time
} process;

/**
 * Μέθοδος για την εύρεση της επόμενης προς εκτέλεσης διεργασίας.
 *
 * @param arr πίνακας που περιέχει τις διεργασίες.
 * @param total_elements πλήθος διεργασιών.
 * @param current_time τρέχουσα χρονική στιγμή.
 * @return min_index, δηλαδή index της διεργασίας με ελάχιστο χρόνο εκτέλεσης.
 */

int find_next_for_execution(process *arr, int total_elements, int current_time)
{
    int min = pow(2, 8), min_index; //  min --> 'μεγάλη' αρχική τιμή για την εύρεση του ελάχιστου burst_time

    for(int i = 0 ; i < total_elements ; i++)
    {
        // Αν η διεργασία δεν έχει τελειώσει και ο χρόνος άφιξης είναι μικρότερος ή ίσος της τρέχουσας χρονικής στιγμής.
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

/**
 * Μέθοδος για τον έλεγχο αν έχει φτάσει καινούργιο process την τρέχουσα χρονική στιγμή.
 *
 * @param arr πίνακας που περιέχει τις διεργασίες.
 * @param total_elements πλήθος διεργασιών.
 * @param current_time τρέχουσα χρονική στιγμή.
 * @return i δηλαδή το index της διεργασίας, αλλιώς επιστρέφει custom value -999.
 */

int check_for_arrival(process *arr, int total_elements, int current_time)
{
    for(int i = 0 ; i < total_elements ;i++)
    {
        if(arr[i].at == current_time)
        {
            return i;
        }
    }
    return -999;
}

/**
 * Μέθοδος για το έλεγχο αν θα γίνει εναλλάγη της τρέχουσας διεργασίας με αυτήν με index_to_chek
 * @param arr πίνακας που περιέχει τις διεργασίες.
 * @param index_to_check index διεργασίας που έχει φτάσει την τρέχουσα χρονική στιγμή.
 * @param current_burst_time burst_time της τρέχουσας διεργασίας.
 * @return επιστρέφει 1 αν θα γίνει εναλλαγή, αλλιώς επιστρέφει 0.
 */

char check_to_change(process *arr, int index_to_check, int current_burst_time)
{
    if(current_burst_time > arr[index_to_check].bt)
    {
        return 1;
    }

    return 0;
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

    int current_time = 0,burst_time, for_execution = 0, processes_finished = 0 ,to_check;

    char normal_exit, change_process;

    //for_execution --> index της διεργασίας που θα εκτελεστεί.
    //processes_finished --> πλήθος διεργασιών που έχουν ολοκληρωθεί.

    //normal_exit --> μεταβλήτη που δείχνει οτι μια διεργασία έχει ολοκληρωθέι και δεν έχει γίνει κάποια εναλλαγή.
    //change_process --> μεταβλήτη που δείχνει αν θα γίνει εναλλαγή διεργασίας (σαν boolean μεταβλητή)

    while(1)
    {
        normal_exit = 1;
        burst_time = arr[for_execution].bt;

        for(int i = 0 ; i < burst_time ;i++)
        {
            current_time ++;
            printf("%d\n",arr[for_execution].pid);
            arr[for_execution].bt--;

            to_check = check_for_arrival(arr,n, current_time);

            if(to_check != -999)
            {
                change_process = check_to_change(arr, to_check,arr[for_execution].bt);

                if(change_process)
                {
                    for_execution = to_check;
                    normal_exit = 0;
                    break;
                }
            }

        }

        if(normal_exit)
        {
            for_execution = find_next_for_execution(arr, n, current_time);
            processes_finished ++;
        }

        //Έχουν ολοκληρωθεί όλες οι διεργασίες.
        if(processes_finished == n)
        {
            break;
        }

    }
    return 0; /* DO NOT EDIT THIS LINE */
}

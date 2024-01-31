#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid; // process ID
    int at; // arrival time
    int bt; // burst time
} process;

/**
 * Μέθοδος που μετατοπίζει τις διεργασίες, η running εργασία τοποθετείται στο τέλος της ουράς, όλες οι
 * υπόλοιπες κάνουν ενα shift αριστερα.
 * @param queue Η ουρά με τις διεργασίες.
 * @param index_of_last index τελευταίου στοιχείου της ουράς.
 * @return Ενημερωμένη ουρά
 */
process* swap_processes(process *queue, int index_of_last)
{
    process temp = queue[0];

    for(int i = 0 ; i <index_of_last ;i ++)
    {
        queue[i] = queue[i + 1]; //shift κατά μια θέση αριστερά.
    }

    queue[index_of_last] = temp;

    return queue;
}

/**
 * Μέθοδος που προσθέτει μια διεργασία στην ουρά των έτοιμων διεργασιών.
 * @param queue Η ουρά με τις διεργασίες.
 * @param total_elements Πλήθος διεργασιών.
 * @param to_add Διεργασία που πρόκειται να προστεθεί.
 * @return Ενημερωμένο ουρά.
 */

process* add_process_to_queque(process *queue, int total_elements, process to_add)
{
    //Το μέγεθος της ουράς αυξάνεται κατά 1.
    queue = (process *) realloc(queue, sizeof(process) * ( total_elements + 1 ));
    queue[total_elements] = to_add; //προσθήκη του στοιχείου.
    return queue;
}

/**
 *  Μέθοδος που αφαιρεί μια διεργασία απο την ουρά των διεργασιών, με την χρήση της realloc() φεύγει
 *  η τελευταία διεργασία.
 * @param queque Η ουρά με τις διεργασίες.
 * @param total_elements Πλήθος διεργασιών.
 * @return Ενημερωμένο ουρά.
 */

process* pop_last_process(process *queque, int total_elements)
{
    //Μέγεθος της ουράς μειώνεται κατά 1, φεύγει το τελευταίο στοιχείο.
    return (process*) realloc(queque, (total_elements - 1) * sizeof(process));
}

int main()
{
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

    int current_time = 0, total_elements = 1;

    char to_swap;

    process* queue = malloc(sizeof(process));

    queue[0] = arr[0];

    while(1)
    {
        to_swap = 1;

        for(int i = 0 ; i < quantum ; i++)
        {
            queue[0].bt--;
            current_time++;

            printf("%d\n", queue[0].pid);

            //Έλεγχος για το αν έχει φτάσει νεα διεργασία.
            for(int j = 0 ; j < n ; j++)
            {
                if(arr[j].at == current_time && arr[j].bt != 0)
                {
                    queue = add_process_to_queque(queue, total_elements, arr[j]);
                    total_elements++;
                }
            }
            //Διεργασία έχει τελειώσει στην διάρκεια του κβάντου, κανω εναλλαγή.
            if(queue[0].bt == 0)
            {
                if(total_elements > 1)
                {
                    queue = swap_processes(queue, total_elements - 1);
                }
                queue = pop_last_process(queue, total_elements);
                total_elements--;
                to_swap = 0;
                break;
            }
        }

        //Έχουν εκτελεστεί όλες οι διεργασίες.
        if(total_elements == 0)
        {
            break;
        }
        //Το κβάντο έχει τελειώσει κάνω εναλλαγή διεργασίας.
        if(to_swap && total_elements > 1)
        {
            queue = swap_processes(queue, total_elements - 1);
        }

    }

    return 0; /* DO NOT EDIT THIS LINE */
}

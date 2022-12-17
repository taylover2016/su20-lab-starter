#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    node* tortoise = head;
    node* hare = head;

    if (hare == NULL)
    {
        return 0;
    }

    hare = hare->next;

    if (hare == NULL)
    {
        return 0;
    }
    else if (hare->next == NULL)
    {
        return 0;
    }

    tortoise = hare;
    hare = hare->next;

    while (hare != tortoise && hare->next != NULL && hare->next->next != NULL)
    {
        hare = hare->next->next;
        tortoise = tortoise->next;
    }
    
    if (hare == tortoise)
    {
        return 1;
    }

    return 0;
}
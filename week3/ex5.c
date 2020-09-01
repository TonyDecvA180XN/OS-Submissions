#include <stdio.h>
#include <stdlib.h>

struct List
{
    struct Node* m_head;
    int size;
};

struct Node
{
    struct Node* m_prev, * m_next;
    int value;
};

void print_list(struct List* list)
{
    if (!list->size) 
    {
        printf("Empty\n"); return;
    }
    struct Node* head = list->m_head;
    while (head)
    {
        printf("%d ", head->value);
        head = head->m_next;
    }
    printf("\n");
    return;
}

void insert_node(struct List* list, int index, int value)
{
    /*
        Traditionally, when we insert element x on index i it means after insertion we have list[i] == x.
        There 5 cases possible:
        1. We insert into empty list
            - add dead end element
            - update head
        2. We insert into beginging
            - add dead end element
            - link next to current
            - link current to next
            - update head
        3. We insert into end
            - find last element
            - add dead end element
            - link current to last
            - link last to curent
        4. General case
            - find first element to shift
            - add dead end element
            - link current to previous
            - link current to next
            - link previous to current
            - link next to current
        5. Wrong index
    */

    // case 5
    if (index < 0 || index > list->size) return;

    // case 1
    if (!list->size)
    {
        // add dead end element
        struct Node* new_node = malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->m_prev = 0;
        new_node->m_next = 0;

        // update head
        list->m_head = new_node;

        ++(list->size);
        return;
    }

    // case 2
    if (!index)
    {
        // add dead end element
        struct Node* new_node = malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->m_prev = 0;
        new_node->m_next = 0;

        // link next to current
        list->m_head->m_prev = new_node;

        // link current to next
        new_node->m_next = list->m_head;

        // update head
        list->m_head = new_node;

        ++(list->size);
        return;
    }

    // case 3
    if (index == list->size)
    {
        // find last element
        struct Node* tail = list->m_head;
        while (tail->m_next) tail = tail->m_next;

        // add dead end element
        struct Node* new_node = malloc(sizeof(struct Node));
        new_node->value = value;
        new_node->m_prev = 0;
        new_node->m_next = 0;

        // link current to last
        new_node->m_prev = tail;

        // link last to current
        tail->m_next = new_node;

        ++(list->size);
        return;
    }

    // general case

    // find first element to shift
    struct Node* border_node = list->m_head;
    for (int i = 0; i < index; ++i)
    {
        border_node = border_node->m_next;
    }

    // add dead end element
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->m_prev = 0;
    new_node->m_next = 0;

    // link current to previous
    new_node->m_prev = border_node->m_prev;

    // link current to next
    new_node->m_next = border_node;

    // link previous to current
    border_node->m_prev->m_next = new_node;

    // link next to current
    border_node->m_prev = new_node;

    ++(list->size);
    return;
}

void delete_node(struct List* list, int index)
{
    /*
        There 5 cases possible:
        1. We are trying to delete from empty list
        2. We delete only element
            - delete node
            - unlink head
        3. We delete first element
            - unlink next from current
            - delete node
            - update head
        4. We delete last element
            - find last element
            - unlink last from current
            - delete node
        5. General case
            - find element to cut
            - link previous to next
            - link next to previous
            - delete node
        6. Wrong index
    */

    // case 6
    if (index < 0 || index > list->size) return;

    // case 1
    if (!list->size) return;

    // case 2
    if (list->size == 1)
    {
        // delete node
        free(list->m_head);

        // unlink head
        list->m_head = 0;

        --(list->size);
        return;
    }

    // case 3
    if (!index)
    {
        // update head
        list->m_head->m_prev = list->m_head;
        list->m_head = list->m_head->m_next;
        
        // delete node
        free(list->m_head->m_prev);

        // unlink next from current
        list->m_head->m_prev = 0;

        --(list->size);
        return;
    }

    // case 4
    if (index == list->size - 1)
    {
        // find last element
        struct Node* tail = list->m_head;
        while (tail->m_next) tail = tail->m_next;

        // unlink last from current
        tail->m_prev->m_next = 0;

        // delete node
        free(tail);

        --(list->size);
        return;
    }

    // general case

    // find  element to cut
    struct Node* border_node = list->m_head;
    for (int i = 0; i < index; ++i)
    {
        border_node = border_node->m_next;
    }

    // link previous to next
    border_node->m_prev->m_next = border_node->m_next;

    // link next to previous
    border_node->m_next->m_prev = border_node->m_prev;

    // delete node
    free(border_node);

    --(list->size);
    return;
}


int main()
{
    struct List* my_list = malloc(sizeof(struct List));
    my_list->m_head = 0;
    my_list->size = 0;


    print_list(my_list);
    insert_node(my_list, 0, 2); // case 1
    print_list(my_list);
    insert_node(my_list, 0, 1); // case 2
    print_list(my_list);
    insert_node(my_list, 2, 4); // case 3
    print_list(my_list);
    insert_node(my_list, 2, 3); // case 4
    print_list(my_list);
    insert_node(my_list, 10, 5); // case 5
    print_list(my_list);

    delete_node(my_list, 123); // case 6
    print_list(my_list);
    delete_node(my_list, 2); // case 5
    print_list(my_list);
    delete_node(my_list, 2); // case 4
    print_list(my_list);
    delete_node(my_list, 0); // case 3
    print_list(my_list);
    delete_node(my_list, 0); // case 2
    print_list(my_list);
    delete_node(my_list, 2); // case 1
    print_list(my_list);

    
    // no memory leaks!
    while (my_list->size)
    {
        delete_node(my_list, 0);
    }
    free(my_list);

    return 0;
}
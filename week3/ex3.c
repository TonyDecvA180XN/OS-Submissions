#include <stdio.h>
#include <stdlib.h>

struct List
{
    struct Node* m_head;
    int size;
};

struct Node
{
    struct Node* m_next;
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
            - link current to next
            - update head
        3. We insert into end
            - find last element
            - add dead end element
            - link last to curent
        4. General case
            - find first element before shift
            - add dead end element
            - link current to next
            - link previous to current
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
        new_node->m_next = 0;

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
        new_node->m_next = 0;

        // link last to current
        tail->m_next = new_node;

        ++(list->size);
        return;
    }

    // general case

    // find first element before the shift
    struct Node* border_node = list->m_head;
    for (int i = 0; i < index - 1; ++i)
    {
        border_node = border_node->m_next;
    }

    // add dead end element
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->m_next = 0;

    // link current to next
    new_node->m_next = border_node->m_next;

    // link previous to current
    border_node->m_next = new_node;

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
            - find the one before last element
            - unlink last from current
            - delete node
        5. General case
            - find element before the one to cut
            - link previous to next
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
        struct Node* old_head = list->m_head;
        list->m_head = list->m_head->m_next;

        // delete node
        free(old_head);

        --(list->size);
        return;
    }

    // case 4
    if (index == list->size - 1)
    {
        // find last element
        struct Node* tail = list->m_head;
        for (int i = 0; i < index - 1; ++i)
            tail = tail->m_next;

        // unlink last from current
        tail->m_next = 0;

        // delete node
        free(tail->m_next);

        --(list->size);
        return;
    }

    // general case

    // find  element before the one to cut
    struct Node* border_node = list->m_head;
    for (int i = 0; i < index - 1; ++i)
    {
        border_node = border_node->m_next;
    }

    // link previous to next
    struct Node* old_border = border_node->m_next;
    border_node->m_next = border_node->m_next->m_next;

    // delete node
    free(old_border);

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
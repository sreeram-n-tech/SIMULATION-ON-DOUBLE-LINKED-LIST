#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;

// Function to create a doubly linked list
void createList() {
    int n, data;
    printf("Enter number of nodes to create: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }
    
    // Clear existing list
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = head;
        newNode->prev = NULL;
        if (head != NULL) head->prev = newNode;
        head = newNode;
    }
    printf("Doubly linked list created with %d nodes.\n", n);
}

// Function to display the doubly linked list
void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to insert a node at the beginning
void insertAtBeginning(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) head->prev = newNode;
    head = newNode;
    printf("Inserted %d at the beginning.\n", data);
}

// Function to insert a node at a specific position (1-based)
void insertAtPosition(int data, int position) {
    if (position <= 0) {
        printf("Position should be >= 1\n");
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    if (head == NULL) {
        if (position != 1) {
            printf("List is empty. Can only insert at position 1.\n");
            free(newNode);
            return;
        }
        head = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
        printf("Inserted %d at position %d.\n", data, position);
        return;
    }
    
    if (position == 1) {
        newNode->next = head;
        newNode->prev = NULL;
        head->prev = newNode;
        head = newNode;
        printf("Inserted %d at position %d.\n", data, position);
        return;
    }

    struct Node* temp = head;
    int count = 1;
    while (count < position - 1 && temp != NULL) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) {
        printf("Position out of range.\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) temp->next->prev = newNode;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", data, position);
}

// Function to delete node at beginning
void deleteAtBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    free(temp);
    printf("Deleted node at beginning.\n");
}

// Function to delete node at a specific position (1-based)
void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (position <= 0) {
        printf("Position should be >= 1\n");
        return;
    }

    if (position == 1) {
        deleteAtBeginning();
        return;
    }

    struct Node* temp = head;
    int count = 1;
    while (count < position - 1 && temp != NULL) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range.\n");
        return;
    }
    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    if (toDelete->next != NULL) toDelete->next->prev = temp;
    free(toDelete);
    printf("Deleted node at position %d.\n", position);
}

// Function to search for a value
int searchNode(int key) {
    if (head == NULL) {
        printf("List is empty.\n");
        return -1;
    }
    
    struct Node* temp = head;
    int position = 1;
    
    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", key, position);
            return position;
        }
        temp = temp->next;
        position++;
    }
    
    printf("Element %d not found in the list.\n", key);
    return -1;
}

int main() {
    int choice, data, position, key;
    while (1) {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Create list\n");
        printf("2. Insert at beginning\n");
        printf("3. Insert at position\n");
        printf("4. Delete at beginning\n");
        printf("5. Delete at position\n");
        printf("6. Display list\n");
        printf("7. Search element\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createList();
                break;
            case 2:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position to insert at: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
            case 4:
                deleteAtBeginning();
                break;
            case 5:
                printf("Enter position to delete from: ");
                scanf("%d", &position);
                deleteAtPosition(position);
                break;
            case 6:
                display();
                break;
            case 7:
                printf("Enter element to search: ");
                scanf("%d", &key);
                searchNode(key);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

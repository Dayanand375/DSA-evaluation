#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Node {
    int data;
    struct Node* next;
};

struct CircularQueue {
    struct Node* front;
    struct Node* rear;
    int size;
    int capacity;
};


int is_empty(struct CircularQueue* queue) {
    return queue->size == 0;
}

int is_full(struct CircularQueue* queue) {
    return queue->size == queue->capacity;
}


struct Node* create_node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(struct CircularQueue* queue, int data) {
    if (is_full(queue)) {
        printf("Circular queue is full.\n");
        return;
    }

    struct Node* newNode = create_node(data);

    if (is_empty(queue)) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }

    queue->rear = newNode;
    queue->rear->next = queue->front;
    queue->size++;

    FILE* file = fopen("enqueued_elements.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d\n", data);
        fclose(file);
    }
}


int dequeue(struct CircularQueue* queue) {
    if (is_empty(queue)) {
        printf("Circular queue is empty.\n");
        return -1;
    }

    int data = queue->front->data;

    if (queue->size == 1) {
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
        free(temp);
    }

    queue->size--;

    FILE* file = fopen("dequeued_elements.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d\n", data);
        fclose(file);
    }

    return data;
}


void display(struct CircularQueue* queue) {
    if (is_empty(queue)) {
        printf("Circular queue is empty.\n");
        return;
    }

    struct Node* current = queue->front;
    printf("Circular queue elements: ");

    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != queue->front);

    printf("\n");
}


void generate_random_numbers(char* file_name, int range_start, int range_end, int count) {
    FILE* file = fopen(file_name, "w");
    if (file != NULL) {
        srand(time(NULL));

        for (int i = 0; i < count; i++) {
            int number = rand() % (range_end - range_start + 1) + range_start;
            fprintf(file, "%d\n", number);
        }

        fclose(file);
    }
}


int* read_numbers_from_file(char* file_name, int count) {
    int* numbers = (int*)malloc(count * sizeof(int));
    FILE* file = fopen(file_name, "r");
    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fscanf(file, "%d", &numbers[i]);
        }
        fclose(file);
    }
    return numbers;
}

int main() {
    int range_start = 1;
    int range_end = 100;
    int count = 10;
    int queue_capacity = 5;


    generate_random_numbers("generated_numbers.txt", range_start, range_end, count);


    int* numbers = read_numbers_from_file("generated_numbers.txt", count);

    // Create the circular queue
    struct CircularQueue queue;
    queue.front = NULL;
    queue.rear = NULL;
    queue.size = 0;
    queue.capacity = queue_capacity;
    int a;
    int i=0;
    int num_dequeued,dequeued;
    while(1)
    {
        printf("1)Enqueue\n2)Dequeue\n3)Display\n4)Exit\n");
        scanf("%d",&a);
        switch(a)
        {

        case 1:
              enqueue(&queue, numbers[i]);
              i++;
               break;
        case 2:num_dequeued = count > queue_capacity ? queue_capacity : count;
                dequeued = dequeue(&queue);
               printf("Dequeued element: %d\n", dequeued);
               break;
        case 4:exit(0);
               default:display(&queue);
        }
    }

    free(numbers);


}

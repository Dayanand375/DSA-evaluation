#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue* q) {
    return (q->rear == MAX_SIZE - 1);
}

int isEmpty(Queue* q) {
    return (q->front == -1);
}

void enqueue(Queue* q, int item) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue element.\n");
    } else {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = item;
        printf("Enqueued item: %d\n", item);
    }
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue element.\n");
        return -1;
    } else {
        int item = q->data[q->front];
        if (q->front == q->rear) {
            // Reset the queue when it becomes empty
            initQueue(q);
        } else {
            q->front++;
        }
        return item;
    }
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue elements:\n");
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->data[i]);
        }
        printf("\n");
    }
}

int main() {
    Queue q;
    initQueue(&q);
    int p, t, qVal, i, num, count1 = 0, count2 = 0;
    FILE* fp1 = fopen("generate.txt", "w");
    printf("Enter the range: ");
    scanf("%d %d", &p, &qVal);
    printf("Enter the number of elements to generate: ");
    scanf("%d", &t);
    FILE* fp5 = fopen("operation.txt", "w");
    fprintf(fp5, "Generated elements are: ");
    for (i = 0; i < t; i++) {
        num = (rand() % (p - qVal + 1)) + p;
        printf("%d\n", num);
        fprintf(fp1, "%d ", num);
        fprintf(fp5, "%d ", num);
    }
    fprintf(fp5, "\n");
    fclose(fp1);
    fp1 = fopen("generate.txt", "r");
    FILE* fp2 = fopen("enqueue.txt", "w");
    FILE* fp3 = fopen("dequeue.txt", "w");
    initQueue(&q);
    int e, ch;
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                if (isFull(&q))
                    printf("Queue overflow\n");
                else {
                    printf("Enter the element: ");
                    fscanf(fp1, "%d ", &e);
                    printf("%d", e);
                    fprintf(fp2, "%d ", e);
                    fprintf(fp5, "Enqueued element is %d\n", e);
                    count1++;
                    enqueue(&q, e);
                }
                break;
            case 2:
                if (isEmpty(&q))
                    printf("Empty Queue\n");
                else {
                    e = dequeue(&q);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Dequeued element is %d\n", e);
                    count2++;
                }
                break;
            case 3:
                display(&q);
                fprintf(fp5, "Numbers of enqueued elements is: %d\n", count1);
                fprintf(fp5, "Total number of dequeued elements is: %d\n", count2);
                fprintf(fp5, "Number of elements left in the queue is: %d\n", count1 - count2);
                break;
            case 4:
                exit(0);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp5);

}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, int e) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return -1;
    }

    int e = s->top->data;
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);

    return e;
}

void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements are:\n");
    Node* current = s->top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    Stack s;
    initStack(&s);
    int p, q, t, i, num;
    FILE* fp1 = fopen("generate.txt", "w");
    printf("Enter the range: ");
    scanf("%d %d", &p, &q);
    printf("Enter the number of elements to generate: ");
    scanf("%d", &t);

    FILE* fp5 = fopen("operation.txt", "w");
    fprintf(fp5, "Generated elements are: ");
    for (i = 0; i < t; i++) {
        num = (rand() % (p - q + 1)) + p;
        printf("%d\n", num);
        fprintf(fp1, "%d ", num);
        fprintf(fp5, "%d ", num);
    }
    fprintf(fp5, "\n");
    fclose(fp1);

    fp1 = fopen("generate.txt", "r");
    FILE* fp2 = fopen("push.txt", "w");
    FILE* fp3 = fopen("pop.txt", "w");

    int e, ch;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (fscanf(fp1, "%d", &e) == 1) {
                    fprintf(fp2, "%d ", e);
                    fprintf(fp5, "Pushed element is %d\n", e);
                    push(&s, e);
                } else {
                    printf("No more elements to push from file.\n");
                }
                break;
            case 2:
                if (!isEmpty(&s)) {
                    e = pop(&s);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Popped element is %d\n", e);
                } else {
                    printf("Stack is empty.\n");
                }
                break;
            case 3:
                display(&s);
                break;
            case 4:
                fclose(fp1);
                fclose(fp2);
                fclose(fp3);
                fclose(fp5);
                exit(0);
        }
    }

}

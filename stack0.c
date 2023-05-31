#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct {
    int top;
    int ele[max];
} stack;

void initstack(stack *s) {
    s->top = 0;
}

int isFull(stack *s) {
    return (s->top == max);
}

void push(stack *s, int e) {
    s->ele[s->top] = e;
    s->top++;
}

int isEmpty(stack *s) {
    return (s->top == 0);
}

int pop(stack *s) {
    s->top--;
    int e = s->ele[s->top];
    return e;
}

void display(stack *s) {
    FILE *fp4 = fopen("stack.txt", "w");
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements are:\n");
        for (int i = s->top - 1; i >= 0; i--) {
            printf("%d\n", s->ele[i]);
            fprintf(fp4, "%d ", s->ele[i]);
        }
    }
}

int main() {
    stack s;
    int p, t, q, i, num, count1 = 0, count2 = 0;
    FILE *fp1 = fopen("generate.txt", "w");
    printf("Enter the range: ");
    scanf("%d %d", &p, &q);
    printf("Enter the number of elements to generate: ");
    scanf("%d", &t);
    FILE *fp5 = fopen("operation.txt", "w");
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
    FILE *fp2 = fopen("push.txt", "w");
    FILE *fp3 = fopen("pop.txt", "w");
    initstack(&s);
    int e, ch;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. File display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (isFull(&s))
                    printf("Stack overflow\n");
                else {
                    printf("Enter the element: ");
                    fscanf(fp1, "%d ", &e);
                    printf("%d", e);
                    fprintf(fp2, "%d ", e);
                    fprintf(fp5, "Pushed element is %d\n", e);
                    count1++;
                    push(&s, e);
                }
                break;
            case 2:
                if (isEmpty(&s))
                    printf("Empty Stack\n");
                else {
                    e = pop(&s);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Popped element is %d\n", e);
                    count2++;
                }
                break;
            case 3:
                display(&s);
                fprintf(fp5, "Numbers of pushed elements is: %d\n", count1);
                fprintf(fp5, "Total number of popped elements is: %d\n", count2);
                fprintf(fp5, "Number of elements left in stack is: %d\n", count1 - count2);
                break;
            case 4:  exit(0); }}}

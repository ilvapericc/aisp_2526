#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    double data;
    struct Node* next;
} Node;

// Push: vraća novi top stoga
Node* push(Node* top, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Greska pri alokaciji memorije!\n");
        return top; // ne uspe, vraća stari top
    }
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

// Pop: vraća novi top stoga i čuva vrednost, 0 = neuspeh
int pop(Node* top, double* value) {
    if (top == NULL) return 0;
    Node* temp = top;
    *value = top->data;
    free(temp);
    return 1;
}

// Funkcija koja evaluira postfiks izraz sa razmacima
int evaluatePostfix(char* expr, double* result) {
    Node* stack = NULL;
    int i = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || (expr[i] == '-' && isdigit(expr[i + 1]))) {
            // Čitanje broja (pozitivnog ili negativnog)
            double num = 0;
            int sign = 1;
            if (expr[i] == '-') {
                sign = -1;
                i++;
            }
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            num *= sign;
            stack = push(stack, num);
        }
        else {
            // Operator
            double b, a;
            // Pop b
            if (stack == NULL) {
                printf("Greska: nedovoljno operanada za operator '%c'\n", expr[i]);
                return 0;
            }
            b = stack->data;
            Node* temp = stack;
            stack = stack->next;
            free(temp);

            // Pop a
            if (stack == NULL) {
                printf("Greska: nedovoljno operanada za operator '%c'\n", expr[i]);
                return 0;
            }
            a = stack->data;
            temp = stack;
            stack = stack->next;
            free(temp);

            switch (expr[i]) {
            case '+': stack = push(stack, a + b); break;
            case '-': stack = push(stack, a - b); break;
            case '*': stack = push(stack, a * b); break;
            case '/':
                if (b == 0) {
                    printf("Greska: deljenje nulom\n");
                    return 0;
                }
                stack = push(stack, a / b);
                break;
            default:
                printf("Nepoznat operator: '%c'\n", expr[i]);
                return 0;
            }
            i++;
        }
    }

    if (stack == NULL) {
        printf("Greska: stog je prazan, nema rezultata\n");
        return 0;
    }

    *result = stack->data;
    free(stack);

    return 1;
}

int main() {
    FILE* file = fopen("postfix.txt", "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Datoteka je prazna!\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    double result;
    if (evaluatePostfix(line, &result)) {
        printf("Rezultat postfiks izraza: %.2lf\n", result);
    }
    else {
        printf("Evaluacija izraza nije uspela.\n");
    }

    return 0;
}

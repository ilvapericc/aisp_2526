#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX INT_MIN   // GLOBALNA VARIJABLA ZA SIGNAL GREŠKE

struct stog {
    int el;
    struct stog* next;
};

int Push(struct stog* s, int x) {
    struct stog* q = (struct stog*)malloc(sizeof(struct stog));
    if (!q) return 0;
    q->el = x;
    q->next = s->next;
    s->next = q;
    return 1;
}

int Pop(struct stog* s) {
    struct stog* temp = s->next;
    if (!temp) return MAX;   // greška

    int n = temp->el;
    s->next = temp->next;
    free(temp);
    return n;
}

void BrisiSve(struct stog* s) {
    while (s->next != NULL)
        Pop(s);
}

int Operacija(int op1, int op2, char operand) {
    switch (operand) {
    case '+': return op2 + op1;
    case '-': return op2 - op1;
    case '*': return op2 * op1;
    case '/':
        if (op1 == 0) {
            printf("Greska: dijeljenje s nulom!\n");
            return MAX;
        }
        return op2 / op1;
    default:
        return MAX;
    }
}

int UcitajPostfix(char* imedatoteke, char postfix[][100]) {
    FILE* f = fopen(imedatoteke, "r");
    if (!f) return -1;

    int n = 0;
    while (n < 100 && fgets(postfix[n], 100, f)) {
        postfix[n][strcspn(postfix[n], "\n")] = '\0';
        n++;
    }
    fclose(f);
    return n;
}

void IzracunajPostfix(struct stog s, char postfix[][100], int brojRedaka) {
    s.next = NULL;
    int op1, op2, rezultat = 0;

    for (int i = 0; i < brojRedaka; i++) {
        char* elem = postfix[i];

        /* PREPOZNAJE I NEGATIVNE BROJEVE */
        if (isdigit(elem[0]) || (elem[0] == '-' && isdigit(elem[1]))) {
            int broj = atoi(elem);
            Push(&s, broj);
        }
        else if (strchr("+-*/", elem[0]) && elem[1] == '\0') {
            op1 = Pop(&s);
            op2 = Pop(&s);

            if (op1 == MAX || op2 == MAX) {
                printf("Greska: stog je prazan!\n");
                BrisiSve(&s);
                return;
            }

            rezultat = Operacija(op1, op2, elem[0]);

            if (rezultat == MAX) {
                BrisiSve(&s);
                return;
            }

            Push(&s, rezultat);
        }
        else {
            printf("Nepoznat element: %s\n", elem);
            BrisiSve(&s);
            return;
        }
    }

    printf("Rezultat: %d\n", rezultat);
    BrisiSve(&s);
}

int main() {
    char imedatoteke[100];
    char postfix[100][100];
    int brojRedaka;

    struct stog s;
    s.next = NULL;

    printf("Unesi ime datoteke:\n");
    scanf("%99s", imedatoteke);

    brojRedaka = UcitajPostfix(imedatoteke, postfix);
    if (brojRedaka == -1) {
        printf("Greska pri otvaranju datoteke.\n");
        return 1;
    }

    printf("\nUcitani postfix izraz:\n");
    for (int i = 0; i < brojRedaka; i++)
        printf("%s\n", postfix[i]);

    printf("\n");
    IzracunajPostfix(s, postfix, brojRedaka);

    return 0;
}

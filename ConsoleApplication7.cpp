#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*6. Napisati program koji pomoću vezanih listi simulira rad:
a) stoga,
b) reda.
*/

struct cvor {
    int broj;
    struct cvor* next;
};

// ---------------- STOG ----------------

int Push(struct cvor* s) {
    int max = 100, min = 10;
    int broj = rand() % (max - min + 1) + min;

    struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
    if (q == NULL || s == NULL)
        return -1;

    while (s->next != NULL)
        s = s->next;

    q->broj = broj;
    q->next = s->next;
    s->next = q;

    return 1;
}

int Pop(struct cvor* s) {
    if (s == NULL || s->next == NULL)
        return -1;

    struct cvor* temp = s->next;

    while (temp->next != NULL) {
        s = temp;
        temp = temp->next;
    }

    s->next = temp->next;
    free(temp);

    return 1;
}

// ---------------- RED ----------------

int Enqueue(struct cvor* r) {
    int max = 100, min = 10;
    int broj = rand() % (max - min + 1) + min;

    struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
    if (q == NULL || r == NULL)
        return -1;

    while (r->next != NULL)
        r = r->next;

    q->broj = broj;
    q->next = r->next;
    r->next = q;

    return 1;
}

int Dequeue(struct cvor* r) {
    if (r == NULL || r->next == NULL)
        return -1;

    struct cvor* temp = r->next;
    r->next = temp->next;
    free(temp);

    return 1;
}

// ---------------- POMOĆNE ----------------

int Ispis(struct cvor* p) {
    if (p == NULL)
        return -1;

    while (p != NULL) {
        printf("%d\t", p->broj);
        p = p->next;
    }
    printf("\n");
    return 1;
}

int BrisiSve(struct cvor* p) {
    struct cvor* temp;
    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    return 1;
}

// ---------------- MAIN ----------------

int main() {
    srand((unsigned)time(NULL));

    struct cvor HeadR, HeadS;
    HeadR.next = NULL;
    HeadS.next = NULL;

    int odabir;
    int status;

    while (1) {
        printf("\n1 - Push (stog)\n");
        printf("2 - Pop (stog)\n");
        printf("3 - Enqueue (red)\n");
        printf("4 - Dequeue (red)\n");
        printf("-1 - Kraj\n");
        scanf("%d", &odabir);

        switch (odabir) {

        case 1:
            status = Push(&HeadS);
            if (status == -1) {
                printf("Neuspjesno.\n");
                BrisiSve(&HeadS);
                break;
            }
            Ispis(HeadS.next);
            break;

        case 2:
            status = Pop(&HeadS);
            if (status == -1) {
                printf("Neuspjesno.\n");
                BrisiSve(&HeadS);
                break;
            }
            Ispis(HeadS.next);
            break;

        case 3:
            status = Enqueue(&HeadR);
            if (status == -1) {
                printf("Neuspjesno.\n");
                BrisiSve(&HeadR);
                break;
            }
            Ispis(HeadR.next);
            break;

        case 4:
            status = Dequeue(&HeadR);
            if (status == -1) {
                printf("Neuspjeh.\n");
                BrisiSve(&HeadR);
                break;
            }
            Ispis(HeadR.next);
            break;

        case -1:
            BrisiSve(&HeadR);
            BrisiSve(&HeadS);
            printf("Kraj.\n");
            return 0;
        }
    }
}

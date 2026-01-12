#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct cvor {
    int el;
    struct cvor* next;
};

int Ispisi(struct cvor* P) {
    if (P == NULL)
        return -1;

    while (P != NULL) {
        printf(" %d", P->el);
        P = P->next;
    }
    printf("\n");
    return 1;
}

int BrisiSve(struct cvor* P) {
    struct cvor* temp;
    while (P != NULL) {
        temp = P->next;
        free(P);
        P = temp;
    }
    return 1;
}

int Pronadji(struct cvor* L, int x) {
    while (L != NULL) {
        if (L->el == x)
            return 1;
        L = L->next;
    }
    return 0;
}

struct cvor* Unija(struct cvor* L1, struct cvor* L2) {
    struct cvor* rezultat = NULL, *p = NULL;

    while (L1 != NULL) {
        if (!Pronadji(rezultat, L1->el)) {
            struct cvor* q = malloc(sizeof(struct cvor));
            if (q == NULL) {
                BrisiSve(rezultat);
                return NULL;
            }

            q->el = L1->el;
            q->next = NULL;

            if (rezultat == NULL) {
                rezultat = q;
                p = q;
            } else {
                p->next = q;
                p = q;
            }
        }
        L1 = L1->next;
    }

    while (L2 != NULL) {
        if (!Pronadji(rezultat, L2->el)) {
            struct cvor* q = malloc(sizeof(struct cvor));
            if (q == NULL) {
                BrisiSve(rezultat);
                return NULL;
            }

            q->el = L2->el;
            q->next = NULL;

            if (rezultat == NULL) {
                rezultat = q;
                p = q;
            } else {
                p->next = q;
                p = q;
            }
        }
        L2 = L2->next;
    }

    return rezultat;
}

struct cvor* Presjek(struct cvor* L1, struct cvor* L2) {
    struct cvor* rezultat = NULL, *p = NULL;

    while (L1 != NULL) {
        if (Pronadji(L2, L1->el) && !Pronadji(rezultat, L1->el)) {
            struct cvor* q = malloc(sizeof(struct cvor));
            if (q == NULL) {
                BrisiSve(rezultat);
                return NULL;
            }

            q->el = L1->el;
            q->next = NULL;

            if (rezultat == NULL) {
                rezultat = q;
                p = q;
            } else {
                p->next = q;
                p = q;
            }
        }
        L1 = L1->next;
    }

    return rezultat;
}

int main() {
    int n, odabir;
    struct cvor Head1, Head2;
    struct cvor* rezultat = NULL;

    Head1.next = NULL;
    Head2.next = NULL;

    printf("Koliko elemenata sadrze obje liste?\n");
    scanf("%d", &n);

    struct cvor* l1 = &Head1;
    struct cvor* l2 = &Head2;

    printf("Unesite elemente prve liste:\n");
    for (int i = 0; i < n; i++) {
        struct cvor* q = malloc(sizeof(struct cvor));
        if (q == NULL) {
            printf("-1\n");
            BrisiSve(Head1.next);
            BrisiSve(Head2.next);
            return -1;
        }
        scanf("%d", &q->el);
        q->next = NULL;
        l1->next = q;
        l1 = q;
    }

    printf("Unesite elemente druge liste:\n");
    for (int i = 0; i < n; i++) {
        struct cvor* q = malloc(sizeof(struct cvor));
        if (q == NULL) {
            printf("-1\n");
            BrisiSve(Head1.next);
            BrisiSve(Head2.next);
            return -1;
        }
        scanf("%d", &q->el);
        q->next = NULL;
        l2->next = q;
        l2 = q;
    }

    while (1) {
        printf("1 - Unija\n2 - Presjek\n-1 - Kraj\n");
        scanf("%d", &odabir);

        switch (odabir) {
        case 1:
            rezultat = Unija(Head1.next, Head2.next);
            if (rezultat == NULL)
                printf("-1\n");
            else {
                Ispisi(rezultat);
                BrisiSve(rezultat);
            }
            break;

        case 2:
            rezultat = Presjek(Head1.next, Head2.next);
            if (rezultat == NULL)
                printf("-1\n");
            else {
                Ispisi(rezultat);
                BrisiSve(rezultat);
            }
            break;

        case -1:
            BrisiSve(Head1.next);
            BrisiSve(Head2.next);
            printf("Kraj.\n");
            return 0;
        }
    }
}

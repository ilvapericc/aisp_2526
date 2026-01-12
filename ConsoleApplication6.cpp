#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*7. Napisati program koji pomoću vezanih listi simulira rad:
a) cirkularnog stoga
b) reda s prioritetom
*/

struct stog {
    int el;
    struct stog* next;
};

struct red {
    int el;
    int prioritet;
    struct red* next;
};

// ---------------- CIRKULARNI STOG ----------------

int DodajCirkularniStog(struct stog* s) {
    struct stog* q, * prvi, * zadnji;
    int min = 10, max = 100;

    q = (struct stog*)malloc(sizeof(struct stog));
    if (q == NULL)
        return -1;

    q->el = rand() % (max - min + 1) + min;

    if (s->next == NULL) {
        s->next = q;
        q->next = q;
        return 1;
    }

    prvi = s->next;
    zadnji = prvi;

    while (zadnji->next != prvi)
        zadnji = zadnji->next;

    zadnji->next = q;
    q->next = prvi;

    return 1;
}

int BrisiCirkularniStog(struct stog* s) {
    struct stog* prvi, * zadnji, * temp;

    if (s->next == NULL)
        return -1;

    prvi = s->next;

    if (prvi->next == prvi) {
        free(prvi);
        s->next = NULL;
        return 1;
    }

    zadnji = prvi;
    temp = s;

    while (zadnji->next != prvi) {
        temp = zadnji;
        zadnji = zadnji->next;
    }

    temp->next = prvi;
    free(zadnji);

    return 1;
}

int BrisiSveS(struct stog* o) {
    struct stog* temp;
    while (o->next != NULL) {
        temp = o->next;
        o->next = temp->next;
        free(temp);
    }
    return 1;
}

// ---------------- RED S PRIORITETOM ----------------

int DodajRed(struct red* r, int x) {
    struct red* q;
    int min = 1, max = 5;

    q = (struct red*)malloc(sizeof(struct red));
    if (q == NULL)
        return -1;

    q->el = x;
    q->prioritet = rand() % (max - min + 1) + min;

    while (r->next != NULL && r->next->prioritet <= q->prioritet)
        r = r->next;

    q->next = r->next;
    r->next = q;

    return 1;
}

int BrisiRed(struct red* r) {
    struct red* temp;

    if (r->next == NULL)
        return -1;

    temp = r->next;
    r->next = temp->next;
    free(temp);

    return 1;
}

int BrisiSveR(struct red* o) {
    struct red* temp;
    while (o->next != NULL) {
        temp = o->next;
        o->next = temp->next;
        free(temp);
    }
    return 1;
}

// ---------------- ISPISI ----------------

int Ispis(struct stog* p) {
    struct stog* prvi = p;

    if (p == NULL)
        return -1;

    do {
        printf("%d\t", p->el);
        p = p->next;
    } while (p != prvi);

    printf("\n");
    return 1;
}

int IspisR(struct red* p) {
    if (p == NULL)
        return -1;

    while (p != NULL) {
        printf("%d\t%d\n", p->el, p->prioritet);
        p = p->next;
    }
    return 1;
}

// ---------------- MAIN ----------------

int main() {
    srand((unsigned)time(NULL));

    struct stog Head1;
    struct red Head2;
    Head1.next = NULL;
    Head2.next = NULL;

    int odabir, odabirS, odabirR;
    int rezultat, ispis;
    int min = 10, max = 100;

    while (1) {
        printf("\n1 - Cirkularni stog\n");
        printf("2 - Red s prioritetom\n");
        printf("-1 - Kraj\n");
        scanf("%d", &odabir);

        switch (odabir) {

        case 1:
            printf("\n3 - Dodaj u stog\n");
            printf("4 - Brisi sa stoga\n");
            printf("-1 - Povratak\n");
            scanf("%d", &odabirS);

            switch (odabirS) {

            case 3:
                rezultat = DodajCirkularniStog(&Head1);
                if (rezultat == -1) {
                    printf("Neuspjesno dodavanje.\n");
                    BrisiSveS(&Head1);
                    break;
                }
                ispis = Ispis(Head1.next);
                if (ispis == -1) {
                    BrisiSveS(&Head1);
                }
                break;

            case 4:
                rezultat = BrisiCirkularniStog(&Head1);
                if (rezultat == -1) {
                    printf("Neuspjesno brisanje.\n");
                    BrisiSveS(&Head1);
                    break;
                }
                ispis = Ispis(Head1.next);
                if (ispis == -1) {
                    BrisiSveS(&Head1);
                }
                break;
            }
            break;

        case 2:
            printf("\n5 - Dodaj u red\n");
            printf("6 - Brisi iz reda\n");
            printf("-1 - Povratak\n");
            scanf("%d", &odabirR);

            switch (odabirR) {

            case 5: {
                int el = rand() % (max - min + 1) + min;
                rezultat = DodajRed(&Head2, el);
                if (rezultat == -1) {
                    printf("Neuspjesno dodavanje.\n");
                    BrisiSveR(&Head2);
                    break;
                }
                ispis = IspisR(Head2.next);
                if (ispis == -1) {
                    BrisiSveR(&Head2);
                }
                break;
            }

            case 6:
                rezultat = BrisiRed(&Head2);
                if (rezultat == -1) {
                    printf("Neuspjesno brisanje.\n");
                    BrisiSveR(&Head2);
                    break;
                }
                ispis = IspisR(Head2.next);
                if (ispis == -1) {
                    BrisiSveR(&Head2);
                }
                break;
            }
            break;

        case -1:
            BrisiSveS(&Head1);
            BrisiSveR(&Head2);
            printf("Kraj programa.\n");
            return 0;
        }
    }
}

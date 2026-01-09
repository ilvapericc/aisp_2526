#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*5. Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je samo da su
sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1∪L2,
b) L1∩ L2.
Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po kojem su
sortirane. */

struct cvor {
	int el;
	struct cvor* next;
};

int Ispisi(struct cvor* P) {
	if (P == NULL) {
		return -1;
	}
	while (P != NULL) {
		printf(" %d", P->el);
		P = P->next;
	}
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
		if (L->el == x) {
			return 1;
		}
		L = L->next;
	}
	return 0;
}

struct cvor* Unija(struct cvor* L1, struct cvor* L2) {
	struct cvor* rezultat = NULL, *p = NULL;
	while (L1 != NULL) {
		if (!Pronadji(rezultat, L1->el)) {
			struct cvor* q;
			q = (struct cvor*)malloc(sizeof(struct cvor));
			q->el = L1->el;
			q->next = NULL;
			if (rezultat == NULL) {
				rezultat = q;
				p = rezultat;
			}
			else {
				p->next = q;
				p = q;
			}
		}
		L1 = L1->next;
	}


	while (L2 != NULL) {
		if (!Pronadji(rezultat, L2->el)) {
			struct cvor* q;
			q = (struct cvor*)malloc(sizeof(struct cvor));
			q->el = L2->el;
			q->next = NULL;
			if (rezultat == NULL) {
				rezultat = q;
				p = rezultat;
			}
			else {
				p->next = q;
				p = q;
			}
		}
		L2 = L2->next;
	}
	return rezultat;
}


struct cvor* Presjek(struct cvor* L1, struct cvor* L2) {
	struct cvor* rezultat= NULL, * p = NULL;
	while (L1 != NULL) {
		if (Pronadji(L2, L1->el) && !Pronadji(rezultat, L1->el)) {
			struct cvor* q;
			q = (struct cvor*)malloc(sizeof(struct cvor));
			q->el = L1->el;
			q->next = NULL;
			if (rezultat == NULL) {
				rezultat = q;
				p = q;
			}
			else {
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
	struct cvor* rezultat;
	Head1.next = NULL;
	Head2.next = NULL;
	printf("Koliko zelite da elemenata sadrze obje liste?\n");
	scanf(" %d", &n);

	struct cvor* l1 = &Head1;
	struct cvor* l2 = &Head2;
	printf("Unesite elemente prve liste za onoliko clanova koliko ste naveli.\n");
	for (int i = 0; i < n; i++) {
		struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
		scanf(" %d", &q->el);
		q->next = NULL;
		l1->next = q;
		l1 = q;
	}
	printf("Unesite elemente druge liste:\n");
	for (int i = 0; i < n; i++) {
		struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
		scanf("%d", &q->el);
		q->next = NULL;
		l2->next = q;
		l2 = q;
	}
	while (1) {
		printf("Sto zelite uciniti s listom?\n Pritisite 1 za uniju, pritisnite 2 za presjek, pritisnite -1 za kraj.\n");
		scanf(" %d", &odabir);

		switch (odabir) {
		case 1:
			rezultat = Unija(Head1.next, Head2.next);
			if (rezultat == NULL) {
				printf("Greska.\n");
			}
			else {
				Ispisi(rezultat);
			}
			BrisiSve(rezultat);
			break;
		case 2:
			rezultat = Presjek(Head1.next, Head2.next);
			if (rezultat == NULL) {
				printf("Greska.\n");
			}
			else {
				Ispisi(rezultat);
			}
			BrisiSve(rezultat);
			break;
		case -1:
			BrisiSve(Head1.next);
			BrisiSve(Head2.next);
			printf("Kraj.\n");
			return 0;
		}
	}
}
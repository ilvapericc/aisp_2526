#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*7. Napisati program koji pomoću vezanih listi simulira rad:
a) cirkularnog stoga (maksimalni broj elemenata na stogu definira korisnik kad se program
pokrene),
b) reda s prioritetom (prioritet može biti od 1-5 i generira se slučajno, a veći broj znači i veći
prioritet).
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100.
*/

// CIRKULARNI STOG
struct stog {
	int el;
	struct stog* next;
};

struct red {
	int el;
	int prioritet;
	struct red* next;
};

int DodajCirkularniStog(struct stog* s) {
	struct stog* q, * prvi, * zadnji;
	int min = 10, max = 100;
	q = (struct stog*)malloc(sizeof(struct stog));
	if (q == NULL) {
		return -1;
	}
	q->el = rand() % (max - min + 1) + min;
	if (s->next == NULL) {
		s->next = q;
		q->next = q;
		prvi = s->next;
		zadnji = prvi;
	}
	prvi = s->next;
	zadnji = prvi;
	while (zadnji->next != prvi) {
		zadnji = zadnji->next;
	}

	zadnji->next = q;
	q->next = prvi;

	return 1;
}

int BrisiCirkularniStog(struct stog* s) {
	struct stog* prvi, * zadnji, * temp;
	if (s->next == NULL) {
		return -1;
	}
	prvi = s->next;
	if (prvi->next == prvi) {
		free(prvi);
		s->next = NULL;  
		return 1;
	}
	zadnji = prvi;
	temp = s;
	while (zadnji->next != prvi) {
		zadnji = zadnji->next;
		temp = temp->next;
	}
	free(zadnji);
	zadnji = temp;
	zadnji->next = prvi;

	return 1;
}
int BrisiSveS(struct stog *o) {
	if (o == NULL) {
		return -1;
	}
	struct stog* temp = o->next;
	while (o->next != NULL) {
		temp = o->next;
		o->next = temp->next;
		free(temp);
	}
}

int BrisiSveR(struct red* o) {
	if (o == NULL) {
		return -1;
	}
	struct red* temp = o->next;
	while (o->next != NULL) {
		temp = o->next;
		o->next = temp->next;
		free(temp);
	}
}
// RED S PRIORITETOM
int DodajRed(struct red* r, int x) {
	struct red* q;
	int min = 1, max = 5;
	q = (struct red*)malloc(sizeof(struct red));
	if (q == NULL) {
		return -1;
	}
	q->el = x;
	q->prioritet = rand() % (max + min - 1) + min;
	while (r->next != NULL && r->next->prioritet <= q->prioritet) {
		r = r->next;
	}
	q->next = r->next;
	r->next = q;

	return 1;
}

int BrisiRed(struct red* r) {
	if (r == NULL) {
		return -1;
	}
	struct red* temp;
	temp = r->next;
	if (r->next == NULL) {
		printf("Prazan red.");

	}
		temp = r->next;
		r->next = temp->next;
		free(temp);
		return 1;
}

int Ispis(struct stog* p) { 
	struct stog* prvi = p;
	if (p == NULL) { return -1;
	}
	do {
		printf("%d \t \t", p->el);
		p = p->next;
	} while (p != prvi);
	return 1; 
}





int IspisR(struct red* p) {
	if (p == NULL) {
		return -1;
	}
	while (p != NULL) {
		printf("%d\t %d \n", p->el, p->prioritet);
		p = p->next;
	}
	return 1;
}



int main() {
	srand((unsigned)time(NULL));
	struct stog Head1;
	struct red Head2;
	Head1.next = NULL;
	Head2.next = NULL;
	int odabir, rezultat, ispis;
	int odabirS, odabirR;
	int min = 10, max = 100;

	while (1) {
		printf("\nOdaberite sa cime zelite raditi.\n");
		printf("\t1 - Cirkularni stog\n");
		printf("\t2 - Red s prioritetom\n");
		printf("\t-1 - Kraj\n");
		scanf(" %d", &odabir);

		switch (odabir) {
		case 1: {
			printf("Radite sa stogom.\n");
			printf("\t3 - Dodaj element u stog\n");
			printf("\t4 - Izbaci element iz stoga\n");
			printf("\t-1 - Povratak\n");
			scanf(" %d", &odabirS);

			switch (odabirS) {
			case 3: {
				rezultat = DodajCirkularniStog(&Head1);
				if (rezultat == -1) printf("Neuspjesno dodavanje.\n");
				ispis = Ispis(Head1.next);
				if (ispis == -1) printf("Greska pri ispisu.\n");
				break;
			}
			case 4: {
				rezultat = BrisiCirkularniStog(&Head1);
				if (rezultat == -1) printf("Neuspjesno brisanje.\n");
				ispis = Ispis(Head1.next);
				if (ispis == -1) printf("Greska pri ispisu.\n");
				break;
			}
			case -1:
				break;
			default:
				printf("Nepoznat odabir.\n");
				break;
			}
			break;
		}

		case 2: {
			printf("Radite sa redom s prioritetom.\n");
			printf("\t5 - Dodaj element u red\n");
			printf("\t6 - Izbaci element iz reda\n");
			printf("\t-1 - Povratak\n");
			scanf(" %d", &odabirR);

			switch (odabirR) {
			case 5: {
				int el = rand() % (max - min + 1) + min;
				rezultat = DodajRed(&Head2, el);
				if (rezultat == -1) printf("Neuspjesno dodavanje.\n");
				ispis = IspisR(Head2.next);
				if (ispis == -1) printf("Greska pri ispisu.\n");
				break;
			}
			case 6: {
				rezultat = BrisiRed(&Head2);
				if (rezultat == -1) printf("Neuspjesno brisanje.\n");
				ispis = IspisR(Head2.next);
				if (ispis == -1) printf("Greska pri ispisu.\n");
				break;
			}
			case -1:
				break;
			default:
				printf("Nepoznat odabir.\n");
				break;
			}
			break;
		}

		case -1:
			BrisiSveS(&Head1);
			BrisiSveR(&Head2);
			printf("Kraj programa.\n");
			return 0;

		default:
			printf("Nepoznat odabir.\n");
			break;
		}
	}

	return 0;
}

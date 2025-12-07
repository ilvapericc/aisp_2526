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

struct cvor {
	int el;
	struct cvor* next;
};

void UnosCirkularniStog(struct cvor* s) {
	struct cvor* q, * prvi, * zadnji;
	int min = 10, max = 100;
	q = (struct cvor*)malloc(sizeof(struct cvor));
	q->el = rand() % (max - min + 1) + min;
	if (s->next == NULL) {
		q->next = q;
		s->next = q;
	}
		prvi = s->next;
		zadnji = prvi;
		while (zadnji->next != prvi) {
			zadnji = zadnji->next;
		}

		q->next = prvi;
		s->next = q;
		zadnji->next = q;

}

struct cvor *BrisiCirkularniStog(struct cvor* s) {
	struct cvor* temp, *zadnji, *prvi;

	if (s->next == NULL) {
		printf("Stog je prazan.\n");
		return s;
	}
	
	temp = s->next;

	if (temp->next == temp) {
		free(temp);
		s->next = NULL;
		return s;
	}
	prvi = s->next;
	zadnji = prvi;

		while (zadnji->next != prvi) {
			zadnji = zadnji->next;
		}
		s->next = temp->next;
		free(temp);
		zadnji->next = s->next;
	
	return s;

}

struct red {
	int el;
	int prioritet;
	struct red* next;
};

// RED S PRIORITETOM
void RedSPrioritetom(struct red* r, int x) {
	struct red* q = (struct red*)malloc(sizeof(struct red));
	if (q == NULL) {
		printf("Neuspjesna alokacija.\n");
	}
	int max = 5, min = 1;
	q->prioritet = rand() % (max - min + 1) + min;
	q->el = x;
	if (r->next == NULL) {
		q->next = NULL;
		r->next = q;
	}
	else
	{
		//priortet sortiram uzlazno, 1 za najveći a 5 za najmanji
		struct red* prev = r;
		struct red* next = r->next;
		while (next != NULL && next->prioritet <= q->prioritet) {
			prev = next;
			next = next->next;
		}

		q->next = next;
		prev->next = q;
	}

	}


void Ispis(struct cvor* p) {
	struct cvor* prvi = p;
	do {
		printf("%d \t \t", p->el);
		p=p->next;
	} while (p != prvi);
}

void IspisR(struct red* p) {
	while (p != NULL) {
		printf("%d\t %d \n", p->el, p->prioritet);
		p = p->next;
	}
}

void Dequeue(struct red* r) {
	struct red* temp;
	temp = r->next;
	if (r->next == NULL) {
		printf("Prazan stog.");

	}
	else {
		temp = r->next;
		r->next = temp->next;
		free(temp);
	}
}


int main() {
	srand((unsigned)time(NULL));
	int odabir;
	struct cvor Head;
	Head.next = NULL;
	struct red HeadR;
	HeadR.next = NULL;
	int stog, red;
	while (1) {
		printf("\nUnesite sa cime zelite raditi.\n");
		printf("\nKliknite 1 za cirkularni stog, 2 za red, 0 za kraj.\n");
		scanf(" %d", &odabir);
		if (odabir == 0) {
			break;
		}
		switch (odabir) {
		case 1:
			printf("\nAko zelite umetnuti neki broj na stog, ukucajte 3, a ako zelite izbaciti iz stoga ukucajte 4.\n");
			scanf(" %d", &stog);
			switch (stog) {
			case 3:
				UnosCirkularniStog(&Head);
				printf("\n");
				Ispis(Head.next);
				break;
			case 4:
				BrisiCirkularniStog(&Head);
				printf("\n");
				Ispis(Head.next);
				break;
			}
			break;
		case 2:
			printf("\nAko zelite umetnuti neki broj u red, ukucajte 5, a ako zelite izbaciti iz reda ukucajte 6.\n");
			scanf("%d", &red);
			switch (red) {
			case 5: {
				int broj;
				printf("Unesite broj:\n");
				scanf(" %d", &broj);
				RedSPrioritetom(&HeadR, broj);
				IspisR(HeadR.next);
				break;
			case 6:
				Dequeue(&HeadR);
				printf("\n");
				IspisR(HeadR.next);
				break;
			}
			}
			break;
		default:
			printf("Pogresan unos.\n");
			break;
		}

	}
	
	return 0;
}
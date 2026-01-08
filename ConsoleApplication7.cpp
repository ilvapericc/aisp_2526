#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*6. Napisati program koji pomoću vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100.
*/
struct cvor {
	int broj;
	struct cvor* next;
};

// za stog - dodavanje na kraj, skidanje s kraja
int Push(struct cvor* s) {
	int max = 100, min = 10;
	int broj;
	broj = rand() % (max - min + 1) + min;
	struct cvor* q;
	q = (struct cvor*)malloc(sizeof(struct cvor));
	if (q == NULL || s == NULL) {
		return -1;
	}
	while (s->next != NULL) {
		s = s->next;
	}
	q->broj = broj;
	q->next = s->next;
	s->next = q;
	return 1;
}

int Pop(struct cvor* s) {
	if (s == NULL) {
		return -1;
	}
	struct cvor* temp = s->next;
	while (temp->next != NULL) {
		s = temp;
		temp = temp->next;
	}
	s->next = temp->next;
	free(temp);


	return 1;
}
// za red - dodavanje na kraj, skidanje s pocetka
int Enqueue(struct cvor* r) {
	int max = 100, min = 10;
	int broj;
	broj = rand() % (max - min + 1) + min;
	struct cvor* q;
	q = (struct cvor*)malloc(sizeof(struct cvor));
	if (q == NULL || r == NULL) {
		return -1;
	}
	while (r->next != NULL) {
		r = r->next;
	}
	q->broj = broj;
	q->next = r->next;
	r->next = q;
	return 1;
}

int Dequeue(struct cvor* r) {
	if (r == NULL) {
		return -1;
	}
	struct cvor* temp = r->next;
	r->next = temp->next;
	free(temp);

	return 1;
}
int Ispis(struct cvor* p) {
	if (p == NULL) {
		return -1;
	}
	while (p != NULL) {
		printf(" %d\t", p->broj);
		p = p->next;
	}
}
int BrisiSve(struct cvor* p) {
	if (p == NULL) {
		return -1;
	}
	struct cvor* temp = p->next;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}



int main() {
	srand((unsigned)time(NULL));
	int odabir;
	struct cvor HeadR, HeadS;
	HeadR.next = NULL;
	HeadS.next = NULL;
	int i;
	int status;
	while (1) {
		printf("Odaberite sto zelite raditi sta stogom, odnosno redom.\n");
		printf("Pritisnite 1 za dodavanje na stog.\n");
		printf("Pritisnite 2 za skidanje sa stoga.\n");
		printf("Pritisnite 3 za dodavanje u red.\n");
		printf("Pritisnite 4 za skidanje s reda.\n");
		printf("Pritisnite -1 za kraj.\n");
		scanf(" %d", &odabir);
			switch (odabir) {
			case 1:
				status = Push(&HeadS);
				if (status == -1) {
					printf("Neuspjesno.\n");
				}
				Ispis(HeadS.next);
				break;
			case 2:
				status = Pop(&HeadS);
				if (status == -1) {
					printf("Neuspjesno.\n");
				}
				Ispis(HeadS.next);
				break;
			case 3:
				status = Enqueue(&HeadR);
				if (status == -1) {
					printf("Neuspjesno.\n");
				}
				Ispis(HeadR.next);
				break;
			case 4:
				status = Dequeue(&HeadR);
				if (status == -1) {
					printf("Neuspjeh.\n");
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
			return 0;
}
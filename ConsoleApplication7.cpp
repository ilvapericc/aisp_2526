#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
//6. Napisati program koji pomoću vezanih listi simulira rad:
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 - 100.

// OPERACIJE SA STOGOM - DODAVANJE NA PRVOG NA POCETAK I SKIDANJE TOG ISTOG S POCETKA (FIFO)

struct stog {
	int el;
	struct stog* next;
};

struct red {
	int el;
	struct red* next;
};

void Push(struct stog* s, int x) {
	struct stog* q;
	q = (struct stog*)malloc(sizeof(struct stog));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
	}
	else {
		q->el = x;
		q->next = s->next;
		s->next = q;
	}

}

void Pop(struct stog* s) {
	struct stog* temp;
	temp = s->next;
	if (s->next == NULL) {
		printf("Prazan stog.");

	}
	else {
		temp = s->next;
		s->next = temp->next;
		free(temp);
	}
}

// OPERACIJE SA REDOM - DODAVANJE NA KRAJ, BRISANJE S POCETKA (FIFO)
void Enqueue(struct red* r, int x) {
	struct red* q;
	q = (struct red*)malloc(sizeof(struct red));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
	}
	else {
		while (r->next != NULL) {
			r = r->next;
		}
		q->el = x;
		q->next = r->next;
		r->next = q;
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

void IspisS(struct stog* P) {
	while (P != NULL) {
		printf("%d", P->el);
		P = P->next;
	}
}

void IspisR(struct red* P) {
	while (P != NULL) {
		printf("%d", P->el);
		P = P->next;
	}
}


int main() {
	struct stog Head;
	Head.next = NULL;
	struct red HeadR;
	HeadR.next = NULL;
	char izbor = 0;
	int brojS, brojR;
	while (1) {
		int odabir;
		printf("\nOdaberite sa cime zelite raditi? Imate 2 opcije: stog i red.\n");
		printf("\nPritisnite 0 za kraj.\n");
		printf("\nPritisnite 1 za stog, a 2 za red.\n");
		scanf("%d", &odabir);
		if (odabir == 0) {
			printf("Kraj");
			break;
		}
		switch (odabir) {
		case 1:
			int odabirstoga;
			printf("Odaberite sto zelite sa stogom: Push ili pop.\n");
			printf("Pritisnite 3 za push elementa, a 4 za pop elementa.\n");
			scanf("%d", &odabirstoga);
			switch (odabirstoga) {
			case 3:
				printf("Ubacite element koji zelite dodati.\n");
				scanf("%d", &brojS);
				Push(&Head, brojS);
				IspisS(Head.next);
				break;
			case 4:
				Pop(&Head);
				IspisS(Head.next);
			}
			break;
		case 2:
			int odabirreda;
			printf("Odaberite sto zelite sa redom: Enqueue ili Dequeue.\n");
			printf("Pritisnite 5 za Enqueue, a 6 za Dequeue.\n");
			scanf("%d", &odabirreda);
			switch (odabirreda) {
			case 5:
				printf("Unesite element koji zelite dodati na kraj liste.\n");
				scanf("%d", &brojR);
				Enqueue(&HeadR, brojR);
				IspisR(HeadR.next);
				break;
			case 6:
				Dequeue(&HeadR);
				IspisR(HeadR.next);
				break;
			}

		default:
			printf("\r\nPogresan izbor <%c>.\r\nPokusajte ponovno.\r\n", izbor);
			break;
		}
	}





	return 0;
}
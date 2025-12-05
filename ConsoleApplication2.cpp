#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//a) dinamički dodaje novi element na početak liste,
//b) ispisuje listu,
//c) dinamički dodaje novi element na kraj liste,
//d) pronalazi element u listi(po prezimenu),
//e) briše određeni element iz liste.
//U zadatku se ne smiju koristiti globalne varijable.

struct Osoba {
	char ime[50];
	char prezime[50];
	int gr;
	struct Osoba* next;
};
// dinamički dodaje novi element na početak liste
void UnosP(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.");
	}
	else {
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;
	}
}
// ispisuje listu
void Ispisi(struct Osoba* o) {
	if (o == NULL) {
		printf("Lista je prazna.\n");
	}
	else {
		while (o != NULL) {
			printf("%s %s %d\n", o->ime, o->prezime, o->gr);
			o = o->next;
		}
	}
}

// dinamički dodaje novi element na kraj liste
void UnosK(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.\n");
	}
	else {
		while (o->next != NULL) {
			o = o->next;
		}
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;
	}
}

// pronalazi element u listi (po prezimenu)
struct Osoba* PronadjiPoPrezimenu(struct Osoba* o, char* prezime) {
	while (o->next != NULL && strcmp(o->prezime, prezime) != 0) {
		o = o->next;
	}

	return o;
}
// briše određeni element iz liste (npr po prezimenu)
struct Osoba* Brisi(struct Osoba* o, char* prezime) {
	struct Osoba* temp;


	while (o->next != NULL && strcmp(o->prezime, prezime) != 0) {
		o = o->next;
	}

	if (o->next == NULL) {     // ***** OVO SPREČAVA NULL DEREFERENCE *****
		printf("Osoba nije pronadjena.\n");
		return NULL;
	}
	temp = o->next;
	o->next = temp->next;
	free(temp);

}
int main() {
	struct Osoba* o;
	struct Osoba Head;
	Head.next = NULL;
	struct Osoba* TraziP = NULL;
	char odabir;
	int gr;
	char ime[30], prezime[30];

	printf("Odaberite sto zelite sa strukturom:\n");
	printf("\t. Unos na pocetak = pritisni broj 1.\n");
	printf("\t. Ispisi listu = pritisni broj 2.\n");
	printf("\t. Dodaj na kraj = pritisni broj 3.\n");
	printf("\t. Pronadji element u listi po prezimenu = pritisni broj 4.\n");
	printf("\t. Izbrisi element u listi po prezimenu = pritisni broj 5.\n");
	scanf(" %c", &odabir);

	while (1) {



		printf("Unesite odabir: ");
		scanf(" %c", &odabir);

		switch (odabir) {

		case '1':
			printf("Unesi ime, prezime i godinu rodjenja:\n");
			scanf("%s %s %d", ime, prezime, &gr);
			UnosP(&Head, ime, prezime, gr);
			Ispisi(Head.next);
			break;

		case '2':
			Ispisi(Head.next);
			break;

		case '3':
			printf("Unesi ime, prezime i godinu rodjenja:\n");
			scanf("%s %s %d", ime, prezime, &gr);
			UnosK(&Head, ime, prezime, gr);
			Ispisi(Head.next);
			break;

		case '4':
			printf("Unesite prezime:\n");
			scanf("%s", prezime);
			TraziP = PronadjiPoPrezimenu(&Head, prezime);
			if (TraziP != NULL)
				printf("%s %s %d\n", TraziP->ime, TraziP->prezime, TraziP->gr);
			else
				printf("Nije pronadjeno.\n");
			break;

		case '5':
			printf("Unesite prezime:\n");
			scanf("%s", prezime);
			Brisi(&Head, prezime);
			Ispisi(Head.next);
			break;

		case 'k':
		case 'K':
			printf("Kraj programa.\n");
			return 0;

		default:
			printf("Pogresan odabir.\n");
		}
	}

	return 0;
}

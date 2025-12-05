#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//3. Prethodnom zadatku dodati funkcije :
//a) dinamički dodaje novi element iza određenog elementa,
//b) dinamički dodaje novi element ispred određenog elementa,
//c) sortira listu po prezimenima osoba,
//d) upisuje listu u datoteku,
//e) čita listu iz datoteke.

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

// __________________ ZADATAK 3 ___________________________

//dinamicki dodaj element iza odredjenog elementa (npr po godini rodjenja)
void UnosIza(struct Osoba* o, int gr, char* ime, char* prezime, int g) {
	struct Osoba* q;
	while (o->next != NULL && o->gr != gr) {
		o = o->next;
	}
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
	}
	else {
		strcpy(o->ime, ime);
		strcpy(o->prezime, prezime);
		o->gr = g;
		q->next = o->next;
		o->next = q;
	}
}


// dinamicki dodaj element ispred odredjenog elementa (isto npr. po godini rodjenja)
void UnosIspred(struct Osoba* o, int gr, char* ime, char* prezime, int g) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
	}
	else {
		while (o->next != NULL && o->next->gr != gr) {
			o = o->next;
		}

		strcpy(o->ime, ime);
		strcpy(o->prezime, prezime);
		o->gr = g;
		q->next = o->next;
		o->next = q;

	}

}

// sortira listu po prezimenima osoba
void SortirajPoPrezimenu(struct Osoba* o) {

	struct Osoba* end = NULL;
	struct Osoba* i, * j, * prev_j, * tmp;

	while (o->next != end)
	{
		i = o;
		prev_j = i->next;
		j = prev_j->next;

		while (j != end)
		{
			if (_strcmpi(prev_j->prezime, j->prezime) < 0)
			{
				prev_j->next = j->next;
				i->next = j;
				j->next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->next;
		}
		end = prev_j;
	}
}

// upisuje u datoteku podatke

void UpisiDatoteka(struct Osoba* o, char* imedatoteke) {
	FILE* f;
	f = fopen(imedatoteke, "w");
	if (f == NULL) {
		printf("Alokacija bezuspjesna.\n");
	}
	else {
		while (f != NULL) {
			fprintf(f, "%s %s %d\n", o->ime, o->prezime, o->gr);
		}
	}
	fclose(f);
}

//cita podatke iz datoteke

void ProcitajDatoteka(struct Osoba* o, char* imedatoteke) {
	FILE* f;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Alokacija bezuspjesna.\n");
	}
	else {
		while (fscanf(f, "%s %s %d", o->ime, o->prezime, &o->gr) == 3) {
			printf("%s %s %d\n", o->ime, o->prezime, o->gr);
		}
	}
	fclose(f);
}



int main() {
	struct Osoba* o;
	struct Osoba Head;
	Head.next = NULL;
	struct Osoba* TraziP = NULL;
	char odabir;
	int gr;
	int el;
	char imedatoteke[30];
	char ime[30], prezime[30];

	printf("Odaberite sto zelite sa strukturom:\n");
	printf("\t. Unos na pocetak = pritisni broj 1.\n");
	printf("\t. Ispisi listu = pritisni broj 2.\n");
	printf("\t. Dodaj na kraj = pritisni broj 3.\n");
	printf("\t. Pronadji element u listi po prezimenu = pritisni broj 4.\n");
	printf("\t. Izbrisi element u listi po prezimenu = pritisni broj 5.\n");
	printf("\t. Dinamicki dodaje novi element iza odredjenog elementa = pritisni broj 6.\n");
	printf("\t Dinamicki dodaje novi element ispred odredjenog elementa = pritisni broj 7.\n");
	printf("\t Sortira listu po prezimenima osoba = pritisni broj 8.\n");
	printf("\t Upisuje podatke u datoteku: pritisni broj 9.\n");
	printf("\t Ispisuje podatke iz datoteke: pritisni broj 10.\n");

	scanf("%c", &odabir);

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
		case '6':
			printf("Iza kojeg elementa zelite dodati novi? (po godini rodjenja)\n");
			scanf(" %d", &el);
			printf("\n Unesite ime, prezime i godinu rodjenja nove osobe.\n");
			scanf(" %s", ime);
			scanf(" %s", prezime);
			scanf(" %d", &gr);
			UnosIza(&Head, el, ime, prezime, gr);
			Ispisi(Head.next);
			break;
		case '7':
			printf("Ispred kojeg elementa zelite dodati novi? (po godini rodjenja)\n");
			scanf(" %d", &el);
			printf("\n Unesite ime, prezime i godinu rodjenja nove osobe.\n");
			scanf(" %s", ime);
			scanf(" %s", prezime);
			scanf(" %d", &gr);
			UnosIspred(&Head, el, ime, prezime, gr);
			Ispisi(Head.next);
			break;
		case '8':
			SortirajPoPrezimenu(&Head);
			Ispisi(Head.next);
			break;
		case '9':
			printf("Unesite ime datoteke.\n");
			scanf(" %s", imedatoteke);
			UpisiDatoteka(&Head, imedatoteke);
			Ispisi(Head.next);
			break;
		case '10':
			printf("Unesite ime datoteke.\n");
			scanf(" %s", imedatoteke);
			ProcitajDatoteka(&Head, imedatoteke);
			Ispisi(Head.next);
			break;

		case 'k':

		case 'K':
			printf("Kraj programa.\n");

		default:
			printf("Pogresan odabir.\n");
		}
	}

	return 0;
}

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
int UnosP(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.");
		return -1;
	}
	else {
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;
	}
	return 1;
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
int UnosK(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Neuspjesna alokacija.\n");
		return -1;
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
	return 1;
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

	if (o->next == NULL) { 
		printf("Osoba nije pronadjena.\n");
		return NULL;
	}
	temp = o->next;
	o->next = temp->next;
	free(temp);
}

// __________________ ZADATAK 3 ___________________________

//dinamicki dodaj element iza odredjenog elementa (npr po godini rodjenja)
int UnosIza(struct Osoba* o, int gr, char* ime, char* prezime, int g) {
	struct Osoba* q;
	while (o->next != NULL && o->gr != gr) {
		o = o->next;
	}
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
		return -1;
	}
	else {
		strcpy(o->ime, ime);
		strcpy(o->prezime, prezime);
		o->gr = g;
		q->next = o->next;
		o->next = q;
	}

	return 1;
}


// dinamicki dodaj element ispred odredjenog elementa (isto npr. po godini rodjenja)
int UnosIspred(struct Osoba* o, int gr, char* ime, char* prezime, int g) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Alokacija neuspjesna.\n");
		return -1;
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
	return 1;

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

int UpisiDatoteka(struct Osoba* o, char* imedatoteke) {
	FILE* f;
	f = fopen(imedatoteke, "w");
	if (f == NULL) {
		printf("Alokacija bezuspjesna.\n");
		return -1;
	}
	else {
		while (f != NULL) {
			fprintf(f, "%s %s %d\n", o->ime, o->prezime, o->gr);
		}
	}
	fclose(f);
	return 1;
}

//cita podatke iz datoteke

int ProcitajDatoteka(struct Osoba* o, char* imedatoteke) {
	FILE* f;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Alokacija bezuspjesna.\n");
		return -1;
	}
	else {
		while (fscanf(f, "%s %s %d", o->ime, o->prezime, &o->gr) == 3) {
			printf("%s %s %d\n", o->ime, o->prezime, o->gr);
		}
	}
	fclose(f);
	return 1;
}



int main() {
	struct Osoba Head;
	Head.next = NULL;

	struct Osoba* TraziP = NULL;
	char odabir;
	int gr, el;
	int status;
	char imedatoteke[30];
	char ime[30], prezime[30];

	while (1) {
		printf("\nOdaberite:\n");
		printf("1 - Unos na pocetak\n");
		printf("2 - Ispisi listu\n");
		printf("3 - Unos na kraj\n");
		printf("4 - Pronadji po prezimenu\n");
		printf("5 - Brisi po prezimenu\n");
		printf("6 - Unos iza elementa\n");
		printf("7 - Unos ispred elementa\n");
		printf("8 - Sortiraj po prezimenu\n");
		printf("9 - Upisi u datoteku\n");
		printf("0 - Procitaj iz datoteke\n");
		printf("K - Kraj\n");

		scanf(" %c", &odabir);

		switch (odabir) {

		case '1':
			scanf("%s %s %d", ime, prezime, &gr);
			status = UnosP(&Head, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu na pocetak.\n");
			break;

		case '2':
			Ispisi(Head.next);
			break;

		case '3':
			scanf("%s %s %d", ime, prezime, &gr);
			status = UnosK(&Head, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu na kraj.\n");
			break;

		case '4':
			scanf("%s", prezime);
			TraziP = PronadjiPoPrezimenu(&Head, prezime);
			if (TraziP != NULL)
				printf("%s %s %d\n", TraziP->ime, TraziP->prezime, TraziP->gr);
			else
				printf("Nije pronadjeno.\n");
			break;

		case '5':
			scanf("%s", prezime);
			if (Brisi(&Head, prezime) == NULL)
				printf("Brisanje nije uspjelo.\n");
			break;

		case '6':
			scanf("%d", &el);
			scanf("%s %s %d", ime, prezime, &gr);
			status = UnosIza(&Head, el, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu iza elementa.\n");
			break;

		case '7':
			scanf("%d", &el);
			scanf("%s %s %d", ime, prezime, &gr);
			status = UnosIspred(&Head, el, ime, prezime, gr);
			if (status == -1)
				printf("Greska pri unosu ispred elementa.\n");
			break;

		case '8':
			SortirajPoPrezimenu(&Head);
			break;

		case '9':
			scanf("%s", imedatoteke);
			status = UpisiDatoteka(Head.next, imedatoteke);
			if (status == -1)
				printf("Greska pri upisu u datoteku.\n");
			break;

		case '0':
			scanf("%s", imedatoteke);
			status = ProcitajDatoteka(&Head, imedatoteke);
			if (status == -1)
				printf("Greska pri citanju datoteke.\n");
			break;

		case 'K':
		case 'k':
			printf("Kraj programa.\n");
			return 0;

		default:
			printf("Pogresan odabir.\n");
		}
	}
}


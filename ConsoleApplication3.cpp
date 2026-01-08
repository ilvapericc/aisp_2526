#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*3. Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke. */

struct Osoba {
	char ime[50];
	char prezime[50];
	int gr;
	struct Osoba* next;
};
//dodaje na pocetak
int UnosP(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		return -1;
	}
	else {
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->gr = gr;
		q->next = o->next;
		o->next = q;

		return 1;
	}

}
//dodaje na kraj
int UnosK(struct Osoba* o, char* ime, char* prezime, int gr) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
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

		return 1;
	}
}
//pronalazi element po prezimenu
struct Osoba* Pronadji(struct Osoba* o, char* prezime) {
	if (o == NULL) {
		return NULL;
	}
	while (o->next != NULL && strcmp(o->prezime, prezime) != 0) {
		o = o->next;
	}
	return o;
}
//ispisuje elemente liste
int Ispis(struct Osoba* o) {
	if (o == NULL) {
		return -1;
	}
	while (o != NULL) {
		printf(" %s %s %d\n", o->ime, o->prezime, o->gr);
		o = o->next;
	}
}

//brise odredjeni elemenat iz liste (npr po prezimenu)
void Brisi(struct Osoba* o, char* prezime) {
	struct Osoba* temp;
	temp = o->next;
	while (temp != NULL && strcmp(temp->prezime, prezime) != 0) {
		o = temp;
		temp = temp->next;
	}
	o->next = temp->next;
	free(temp);
}

int BrisiSve(struct Osoba* o) {
	if (o == NULL) {
		return -1;
	}
	struct Osoba* temp = o->next;
	while (o->next != NULL) {
		temp = o->next;
		o->next = temp->next;
		free(temp);
	}
}

// dinamicki dodaje novi element iza odredjenog elementa (prema godini rodjenja)
int DodajNoviIza(struct Osoba* o, char* ime, char* prezime, int gr, int godina ) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		return -1;
	}
	while (o->next != NULL && o->gr != godina) {
		o = o->next;
	}
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->gr = gr;
	q->next = o->next;
	o->next = q;
	return 1;

}

// dinamicki dodaje novi element ispred odredjenog elementa(prema godini rodjenja)
int DodajNoviIspred(struct Osoba* o, char* ime, char* prezime, int gr, int godina) {
	struct Osoba* q;
	q = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		return -1;
	}
	while (o->next != NULL && o->next->gr != gr) {
		o = o->next;
	}

	strcpy(o->ime, ime);
	strcpy(o->prezime, prezime);
	o->gr = g;
	q->next = o->next;
	o->next = q;

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
	int odabir;
	int gr, status;
	char ime[30], prezime[30];
	while (1) {
		printf("Unesite koju opciju zelite dodati, za kraj dodajte -1\n");
		printf(" 1 za unos na pocetak.\n");
		printf(" 2 za unos na kraj.\n");
		printf(" 3 za ispis.\n");
		printf(" 4 za pronalazenje elemenata po prezimenu.\n");
		printf(" 5 za brisanje odredenog elementa iz liste.\n");
		printf(" -1 za kraj.\n");
		scanf(" %d", &odabir);
		switch (odabir) {
		case 1:
			printf("Unesite ime i prezime te godinu rodjenja osobe koju zelite unijeti na pocetak.\n");
			scanf(" %s %s %d", ime, prezime, &gr);
			status = UnosP(&Head, ime, prezime, gr);
			if (status == -1) {
				printf("Unos neuspjesan.\n");
			}
			else {
				printf("Uspjesno dodano na pocetak.\n");
			}
			Ispis(Head.next);

			break;
		case 2:
			printf("Unesite ime i prezime te godinu rodjenja osobe koju zelite unijeti na pocetak.\n");
			scanf(" %s %s %d", ime, prezime, &gr);
			status = UnosK(&Head, ime, prezime, gr);
			if (status == -1) {
				printf("Unos neuspjesan.\n");
			}
			else {
				printf("Uspjesno dodano na kraj.\n");
			}
			Ispis(Head.next);

			break;

		case 3:
			status = Ispis(Head.next);
			if (status == -1) {
				printf("Prazna vezana lista.\n");
			}
			else {
				printf("Ispis uspjesan.\n");
			}

			break;
		case 4:
			printf("Unesite prezime po kojem zelite pronaci element liste.\n");
			scanf(" %s", prezime);
			TraziP = Pronadji(&Head, prezime);
			if (TraziP == NULL) {
				printf("Pronalazak neuspjesan.\n");
			}
			else {
				printf("%s %s %d", TraziP->ime, TraziP->prezime, TraziP->gr);
			}
			break;

		case 5:
			printf("Unesite prezime po kojem zelite obrisati element.\n");
			scanf(" %s", prezime);
			Brisi(&Head, prezime);
			Ispis(Head.next);
			break;
		case -1:
			printf("Kraj programa.\n");
			return 0;
		}


	};
	BrisiSve(&Head);

	return 0;
}
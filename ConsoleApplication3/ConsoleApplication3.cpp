/*3. Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Person* Osoba;
struct Person {

	char ime[50];
	char prezime[50];
	int gr;
	Osoba next;
};

// dinamicki dodaje novi element na pocetak liste
void UnosP(Osoba P, char* ime, char* prezime, int gr) {
	Osoba q;
	q = (Osoba)malloc(sizeof(struct Person));
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->gr = gr;

	q->next = P->next;
	P->next = q;

}

//ispisuje listu

void Ispis(Osoba P) {
	P = P->next;
	printf("Ispis:\n");
	while (P != NULL) {
		printf("\n%s %s %d\n", P->ime, P->prezime, P->gr);
		P = P->next;
	}

}

// unos elemenata na kraj

void UnosK(Osoba P, char* ime, char* prezime, int gr) {
	Osoba q;

	while (P->next != NULL) {
		P = P->next;
	}
	q = (Osoba)malloc(sizeof(struct Person));
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->gr = gr;
	q->next = NULL;

	q->next = P->next;
	P->next = q;

}


// Brisanje elemenata po prezimenu

Osoba TraziPret(Osoba P, char* ime) { //pomocna funkcija za brisanje
	while (P->next != NULL && strcmp(P->next->ime, ime) != 0) {
		P = P->next;
	}

	if (P->next != NULL) {
		return P;
	}
	else {
		return NULL;
	}
}
void Brisi(Osoba P, char* ime) {
	Osoba temp;
	P = TraziPret(P, ime);
	if (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

}


// pronalazi element u listi(po prezimenu)

void PronadjiPoPrezimenu(Osoba P, char* prezime) {
	P = P->next;
	while (P != NULL && strcmp(P->prezime, prezime) != 0) {
		P = P->next;
	}

	printf("%s %s %d", P->ime, P->prezime, P->gr);
}


//dodavanje elementa iza odredjenog elementa 


Osoba Trazi(Osoba P, char* ime) { //pomocna funkcija
	P = P->next;
	while (P != NULL && strcmp(P->ime, ime) != 0) {
		P = P->next;
	}


	return P;
}

void UnosIza(Osoba P, char* ime, char* tempime, char* tempprezime, int tempgr) {
	Osoba q;
	P = Trazi(P, ime);
	q = (Osoba)malloc(sizeof(struct Person));
	strcpy(q->ime, tempime);
	strcpy(q->prezime, tempprezime);
	q->gr = tempgr;
	q->next = P->next;
	P->next = q;
}

//dodavanje elementa ispred odredjenog
void UnosIspred(Osoba P, char *ime, char *tempime, char *tempprezime, int tempgr){
	Osoba q;
	P = TraziPret(P, ime);
	if (P == NULL) {
		printf("Osoba s imenom '%s' nije pronadjena.\n", ime);
		return;
	}
	q = (Osoba)malloc(sizeof(struct Person));
	strcpy(q->ime, tempime);
	strcpy(q->prezime, tempprezime);
	q->gr = tempgr;

	q->next = P->next;
	P->next = q;

	}


void Sortiraj(Osoba P) {
	if (P->next == NULL || P->next->next == NULL) return; // lista prazna ili samo jedan element

	Osoba i, j;
	char tempIme[50], tempPrezime[50];
	int tempGr;

	for (i = P->next; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (_strcmpi(i->prezime, j->prezime) > 0) { // uzlazno
				// zamjena sadržaja, ne pokazivača
				strcpy(tempIme, i->ime);
				strcpy(tempPrezime, i->prezime);
				tempGr = i->gr;

				strcpy(i->ime, j->ime);
				strcpy(i->prezime, j->prezime);
				i->gr = j->gr;

				strcpy(j->ime, tempIme);
				strcpy(j->prezime, tempPrezime);
				j->gr = tempGr;
			}
		}
	}
}


void Upisi(char* imedatoteke, Osoba P) {
	FILE* f;
	f = fopen(imedatoteke, "w");
	if (f == NULL) {
		printf("Datoteka nije ucitana.\n");
	}
	P = P->next;
	while (P != NULL) {
		fprintf(f, "%s %s %d\n", P->ime, P->prezime, P->gr);
		P = P->next;
	}

	fclose(f);
}

void Procitaj(char* imedatoteke, Osoba P) {
	FILE* f;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Datoteka nije ucitana.\n");
	}

	printf("Ispis iz datoteke:\n");
	while (P != NULL && fscanf(f, "%s %s %d", P->ime, P->prezime, &P->gr) == 3) {
		printf(" %s %s %d\n", P->ime, P->prezime, P->gr);
		P = P->next;
	}
}

int main() {

	struct Person Head;
	Head.next = NULL;
	char ime[50], prezime[50];
	int gr;
	printf("Unesi 5 imena i prezimena i godinu rodjenja osobe.\n");
	for (int i = 0; i < 5; i++) {
		scanf(" %s %s %d", ime, prezime, &gr);
		UnosK(&Head, ime, prezime, gr);
	}
	Ispis(&Head);

	printf("\nUnesi ime, prezime i godinu rodjenja koju cemo ubaciti na kraj liste:\n");
	scanf(" %s %s %d", ime, prezime, &gr);
	UnosK(&Head, ime, prezime, gr);
	Ispis(&Head);


	printf("\nUnesi ime osobe koju zelite izbrisati iz liste.\n");
	scanf(" %s", ime);
	Brisi(&Head, ime);
	Ispis(&Head);

	printf("Unesite osobu koju zelite pronaci po njenom prezimenu:\n");
	scanf(" %s", prezime);
	PronadjiPoPrezimenu(&Head, prezime);


	printf("\n\nIza koga zelite umetnuti novu osobu? (samo ime)\n");
	scanf("%s", ime);
	char tempime[20], tempprezime[20];
	int tempgr;
	printf("\nUnesite ime, prezime i godinu rodjenja za osobu koju zelite ubaciti u listu.\n");
	scanf(" %s %s %d", tempime, tempprezime, &tempgr);
	UnosIza(&Head, ime, tempime, tempprezime, tempgr);
	printf("\n");
	Ispis(&Head);

	printf("\n\nIspred koje osobe zelite unijeti novu osobu? (samo ime)");
	scanf("%s", ime);
	printf("\n\nUnesite ime, prezime i godinu rodjenja nove osobe.");
	scanf("%s %s %d", tempime, tempprezime, &tempgr);

	UnosIspred(&Head, ime, tempime, tempprezime, tempgr);
	Ispis(&Head);

	//Sortiraj(&Head);
	//Ispis(&Head);

	char imedatoteke[40];
	printf("\nUnesi ime datoteke u koju zelite upisati podatke.\n");
	scanf(" %s", imedatoteke);
	Upisi(imedatoteke, &Head);
	Procitaj(imedatoteke, &Head);
	return 0;

}
/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable. */

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
void UnosP(Osoba P, char *ime, char* prezime, int gr) {
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

void UnosK(Osoba P, char *ime, char *prezime, int gr) {
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

Osoba TraziPret(Osoba P, char* prezime) { //pomocna funkcija za brisanje
	while (P->next != NULL && strcmp(P->next->prezime, prezime) != 0) {
		P = P->next;
	}

	return P;
}
void Brisi(Osoba P, char* prezime) {
	Osoba temp;
	P = TraziPret(P, prezime);
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

int main() {

	struct Person Head;
	Head.next = NULL;
	char ime[50], prezime[50];
	int gr;
	printf("Unesi 5 imena i prezimena i godinu rodjenja osobe.\n");
	for (int i = 0; i < 5; i++) {
		scanf(" %s %s %d", ime, prezime, &gr);
		UnosP(&Head, ime, prezime, gr);
	}
	Ispis(&Head);

	printf("\nUnesi ime, prezime i godinu rodjenja koju cemo ubaciti na kraj liste:\n");
	scanf(" %s %s %d", ime, prezime, &gr);
	UnosK(&Head, ime, prezime, gr);
	Ispis(&Head);


	printf("\nUnesi prezime osobe koju zelite izbrisati iz liste.\n");
	scanf(" %s", prezime);
	Brisi(&Head, prezime);
	Ispis(&Head);

	printf("Unesite osobu koju zelite pronaci po njenom prezimenu:\n");
	scanf(" %s", prezime);
	PronadjiPoPrezimenu(&Head, prezime);
	return 0;

}
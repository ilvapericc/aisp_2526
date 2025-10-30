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
typedef struct Osoba* Osoba;
 struct Osoba {

	char ime[50];
	char prezime[50];
	int gr;
	Osoba* next;
};

 // dinamicki dodaje novi element na pocetak liste
 void UnosP( Osoba P, char *ime, char *prezime, int gr) {
	 Osoba q;
	 q = (Osoba)malloc(sizeof(struct Osoba));
	 q->ime = ime;
	 q->prezime = prezime;
	 q->gr = gr;
	 q->next = P->next;
	 P->nexr = q;

 }

 //ispisuje listu
int main() {

	struct Osoba Head;
	Head.next = NULL;



	UnosP(&Head, Petra, Petrovic, 2003);
	UnosP(&Head, Luka, Lukic, 2002);
	UnosP(&Head, Marko, Markic, 2004);
	UnosP(&Head, Ante, Ivic, 2005);
	UnosP(&Head, Iva, Ivic, 1999);


	return 0;

}
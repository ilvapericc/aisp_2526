/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj.koliko ima studenata zapisanih u
datoteci.Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata(ime, prezime,
	bodovi) i učitati iz datoteke sve zapise.Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
	Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
	relativan_br_bodova = br_bodova / max_br_bodova * 100*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
	char ime[50];
	char prezime[50];
	float bodovi;
};

int ProcitajRetke(char* imedatoteke) {
	FILE* f;
	char s[100];
	int i = 0;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		return -1;
	}
	else {
		while (fgets(s, 100, f)) {
			i++;
		}
		fclose(f);
		return i;
	}
}

int UcitajPodatke(int br, char *imedatoteke, struct Student *s) {
	FILE* f;
	f = fopen(imedatoteke, "r"); 
	if (f == NULL) {
		return -1;
	}
	else {
		
		for (int i = 0; i < br; i++) {
			fscanf(f, "%s %s %f", s[i].ime, s[i].prezime, &s[i].bodovi);
		}
		fclose(f);
		return 1;
	}
}

void ObradaPodataka(int br, struct Student s[]) {
	float relativan_broj_bodova;
	

	for (int i = 0; i < br; i++) {
		relativan_broj_bodova = (s[i].bodovi / 100) * 100;
		printf("\n%s %s %f - %.2f\n", s[i].ime, s[i].prezime, s[i].bodovi, relativan_broj_bodova);
	}

}


int main() {
	char imedatoteke[100];
	printf("Unesite ime datoteke.\n");
	scanf(" %s", imedatoteke);

	int br = ProcitajRetke(imedatoteke);
	if (ProcitajRetke(imedatoteke) == -1) {
		printf("Neuspjesno otvaranje datoteke.\n");
	}

	struct Student* s = (struct Student*)malloc(br * sizeof(struct Student));
	printf("Ispis podataka:\n");
	UcitajPodatke(br, imedatoteke, s);
	ObradaPodataka(br, s);
	return 0;
}
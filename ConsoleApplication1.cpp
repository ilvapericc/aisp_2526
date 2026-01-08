#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u
datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime,
bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relativan_br_bodova = br_bodova/max_br_bodova*100
*/

struct Student {
	char ime[50];
	char prezime[50];
	int bodovi;
};

int ProcitajStudente(char* imedatoteke) {
	FILE* f;
	int i = 0;
	char ime[50], prezime[50];
	int bodovi;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Datoteka nije ucitana.\n");
	}
	else {
		while (fscanf(f, "%s %s %d", ime, prezime, &bodovi) == 3) {
			i++;
		}
	}
	fclose(f);
	return i;
}

int UcitajIspisi(struct Student s[], char* imedatoteke, int br) {
	FILE* f;
	int i = 0;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Datoteka nije ucitana.\n");
		return -1;
	}
	else {
		while (fscanf(f, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi) == 3) {
			i++;
		}
	}

	float maxBodovi = s[0].bodovi;
	for (int i = 0; i < br; i++) {
		if (s[i].bodovi > maxBodovi) {
			maxBodovi = s[i].bodovi;
		}
	}

	float relativanbrojbodova;
	for (int i = 0; i < br; i++) {
		relativanbrojbodova = (s[i].bodovi / maxBodovi) * 100;
		printf("%s %s %d %f\n", s[i].ime, s[i].prezime, s[i].bodovi, relativanbrojbodova);
	}

	return 1;
}

int main() {
	char imedatoteke[50];
	printf("Unesite ime datoteke.\n");
	scanf("%s", imedatoteke);
	int br = ProcitajStudente(imedatoteke);
	if (br == 0) {
		printf("Nema zapisa u datoteci.\n");
		return 0;
	}
	struct Student* s = ((struct Student*)malloc(br * sizeof(struct Student)));
	if (s == NULL) {
		printf("Neuspjesna alokacija.\n");
		return 0;
	}
	if (UcitajIspisi(s, imedatoteke, br) == -1) {
		printf("Greska pri ucitavanju.\n");
	}
	free(s);
	return 0;
}

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

int IzbrojiStudente(char* imedatoteke) {
	FILE* f;
	f = fopen(imedatoteke, "r");
	if (f == NULL) {
		printf("Datoteka nije ucitana.\n");
	}
	int i = 0;
	char ime[50], prezime[50];
	int bodovi;

	while (fscanf(f, " %s %s %d", ime, prezime, &bodovi) == 3) {
		i++;
	}
	fclose(f);
	return i;
}


int ProcitajStudente(char* imedatoteke, struct Student s[]) {
	int i = 0;
	FILE* f;
	f = fopen(imedatoteke, "r");
	if (!f) {
		printf("Datoteka nije ucitana.\n");
	}

	while (fscanf(f, " %s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi) == 3) {
		i++;
	}
	return i;
}
int maxBroj(struct Student s[], char* imedatoteke) {

	int n = IzbrojiStudente(imedatoteke);
	int max = s[0].bodovi;
	for (int i = 0; i < n; i++) {
		if (s[i].bodovi > max) {
			max = s[i].bodovi;
		}
	}
	return max;
}
void IspisPodataka(struct Student s[], int n, char* imedatoteke) {
	n = ProcitajStudente(imedatoteke, s);
	int max = maxBroj(s, imedatoteke);
	float relativni;
	for (int i = 0; i < n; i++) {
		relativni = (float)s[i].bodovi / max * 100;
		printf("%s %s %d %f\n", s[i].ime, s[i].prezime, s[i].bodovi, relativni);
	}
}


int main() {

	char imedatoteke[100];
	printf("Unesite ime datoteke.\n");
	scanf(" %s", imedatoteke);
	int br = IzbrojiStudente(imedatoteke);
	struct Student* studenti = (struct Student*)malloc(br * sizeof(struct Student));
	ProcitajStudente(imedatoteke, studenti);
	IspisPodataka(studenti, br, imedatoteke);
	free(studenti);
	return 0;
}
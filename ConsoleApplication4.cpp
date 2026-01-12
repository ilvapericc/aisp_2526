int main() {
    struct cvor Head1 = { 0,0,NULL }, Head2 = { 0,0,NULL };
    struct cvor ZbrojRez = { 0,0,NULL }, ProduktRez = { 0,0,NULL };
    int status;

    char imedatoteke1[50], imedatoteke2[50];

    printf("Unesi ime prve datoteke: ");
    scanf("%s", imedatoteke1);
    printf("Unesi ime druge datoteke: ");
    scanf("%s", imedatoteke2);

    status = UcitajPolinome(imedatoteke1, imedatoteke2, &Head1, &Head2);
    if (status == -1) {
        printf("Greska pri ucitavanju datoteka!\n");
        BrisiSve(&Head1);
        BrisiSve(&Head2);
        return -1;
    }

    printf("Polinom P1:\n");
    IspisiPolinom(&Head1);

    printf("Polinom P2:\n");
    IspisiPolinom(&Head2);

    status = ZbrojiPolinome(&Head1, &Head2, &ZbrojRez);
    if (status == -1) {
        printf("Greska pri zbrajanju!\n");
        BrisiSve(&Head1);
        BrisiSve(&Head2);
        BrisiSve(&ZbrojRez);
        return -1;
    }

    printf("Zbroj polinoma:\n");
    IspisiPolinom(&ZbrojRez);

    status = MnozenjePolinoma(&Head1, &Head2, &ProduktRez);
    if (status == -1) {
        printf("Greska pri mnozenju!\n");
        BrisiSve(&Head1);
        BrisiSve(&Head2);
        BrisiSve(&ZbrojRez);
        BrisiSve(&ProduktRez);
        return -1;
    }

    printf("Produkt polinoma:\n");
    IspisiPolinom(&ProduktRez);

    /* Zavrsno ciscenje memorije */
    BrisiSve(&Head1);
    BrisiSve(&Head2);
    BrisiSve(&ZbrojRez);
    BrisiSve(&ProduktRez);

    return 0;
}

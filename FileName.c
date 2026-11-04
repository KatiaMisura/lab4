#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int koef;
    int exp;
} Clan;


void dodaj(Clan p[], int* n, int koef, int exp) {
    if (koef == 0)
        return;

    
    for (int i = 0; i < *n; i++) {
        if (p[i].exp == exp) {
            p[i].koef += koef;
            return;
        }
    }

    p[*n].koef = koef;
    p[*n].exp = exp;
    (*n)++;
}


void sortiraj(Clan p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].exp < p[j].exp) {
                Clan temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}


void ispisi(Clan p[], int n) {
    int prvi = 1;

    sortiraj(p, n);

    for (int i = 0; i < n; i++) {
        if (p[i].koef == 0)
            continue;

        if (!prvi && p[i].koef > 0)
            printf(" + ");
        else if (p[i].koef < 0)
            printf(" - ");

        if (prvi && p[i].koef < 0)
            printf("-");

        int k = abs(p[i].koef);

        if (p[i].exp == 0)
            printf("%d", k);
        else if (p[i].exp == 1) {
            if (k != 1)
                printf("%d", k);
            printf("x");
        }
        else {
            if (k != 1)
                printf("%d", k);
            printf("x^%d", p[i].exp);
        }

        prvi = 0;
    }

    if (prvi)
        printf("0");

    printf("\n");
}


void zbroji(Clan p1[], int n1, Clan p2[], int n2,
    Clan rez[], int* nr) {

    *nr = 0;

    for (int i = 0; i < n1; i++)
        dodaj(rez, nr, p1[i].koef, p1[i].exp);

    for (int i = 0; i < n2; i++)
        dodaj(rez, nr, p2[i].koef, p2[i].exp);
}


void pomnozi(Clan p1[], int n1, Clan p2[], int n2,
    Clan rez[], int* nr) {

    *nr = 0;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            int koef = p1[i].koef * p2[j].koef;
            int exp = p1[i].exp + p2[j].exp;

            dodaj(rez, nr, koef, exp);
        }
    }
}

int main() {
    FILE* dat;
    Clan p1[MAX], p2[MAX];
    Clan zbroj[MAX], produkt[MAX];

    int n1 = 0, n2 = 0;
    int nz, np;
    int koef, exp;

    dat = fopen("polinomi.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    
    while (fscanf(dat, "%d %d", &koef, &exp) == 2) {
        dodaj(p1, &n1, koef, exp);

        if (feof(dat))
            break;

        
        if (fscanf(dat, "%d", &koef) != 1)
            break;

       
    }

    fclose(dat);

    

    return 0;
}

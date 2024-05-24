#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 1000000 //13 pour les tests

void echanger(long long unsigned int *x, long long unsigned int *y) { //ici, long long unsigned int et pas juste uint64_t car pas assez long (unsigned rajoute de la place)
    long long unsigned int temp = *x;
    *x = *y;
    *y = temp;
}

void entasser(long long unsigned int A[], int n, int i) {
    int plus_grand = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && A[gauche] > A[plus_grand])
        plus_grand = gauche;

    if (droite < n && A[droite] > A[plus_grand])
        plus_grand = droite;

    if (plus_grand != i) {
        echanger(&A[i], &A[plus_grand]);
        entasser(A, n, plus_grand);
    }
}

void triParTas(long long unsigned int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasser(A, n, i);

    for (int i = n - 1; i > 0; i--) {
        echanger(&A[0], &A[i]);
        entasser(A, i, 0);
    }
}

int main() {
    //Ouverture du fichier d'entrée
    FILE *file_in;
    file_in = fopen("references.txt", "r"); //"references-test.txt" pour le test avec 13 références
    if (file_in == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée.\n");
        return 1;
    }

    //Création du tableau contenant les références
    long long unsigned int *tab = ( long long unsigned int  *)malloc(SIZE * sizeof( long long unsigned int ));
    if (tab == NULL) {
        printf("Allocation de mémoire a échoué.\n");
        fclose(file_in);
        return 1;
    }

    //Remplissage du tableau de références
    int i = 0;
    while (fscanf(file_in, "%llu", &tab[i]) != EOF && i < SIZE) {
        i++;
    }
    fclose(file_in);

    // Tri par tas du tableau
    triParTas(tab, SIZE);

    // Écriture du tableau trié dans le fichier de sortie
    FILE *file_out;
    file_out = fopen("references-tri-tas.txt", "w");
    if (file_out == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        free(tab);
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        fprintf(file_out, "%llu \n", tab[i]);
        //printf( "%llu \n", tab[i]);
    }
    fclose(file_out);

    //Libération de la mémoire allouée
    free(tab);

    return 0;
}

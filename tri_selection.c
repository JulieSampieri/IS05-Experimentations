#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Inclure pour uint64_t

#define SIZE 13 //pour le test

void TriParSelection(uint64_t *tab, int n) { //utilisation de pointeurs
    uint64_t *fin = tab + n;

    for (uint64_t *i = tab; i < fin - 1; i++) {
        uint64_t *min = i;
        for (uint64_t *j = i + 1; j < fin; j++) {
            if (*j < *min)
                min = j;
        }
        if (min != i) {
            uint64_t tmp = *i;
            *i = *min;
            *min = tmp;
        }
    }
}

int main() {
    //Ouverture du fichier d'entrée
    FILE *file_in;
    file_in = fopen("references-test.txt", "r");
    if (file_in == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée.\n");
        return 1;
    }

    //Création du tableau contenant les références
    uint64_t *tab = (uint64_t *)malloc(SIZE * sizeof(uint64_t));
    if (tab == NULL) {
        printf("Allocation de mémoire a échoué.\n");
        fclose(file_in);
        return 1;
    }

    //Remplissage du tableau de références
    int i = 0;
    while (i < SIZE && fscanf(file_in, "%llu", &tab[i]) != EOF) { // Utilise %llu pour uint64_t
        i++;
    }
    fclose(file_in);

    // Tri par sélection du tableau
    TriParSelection(tab, i); // Passer la taille réelle du tableau

    // Écriture du tableau trié dans le fichier de sortie
    FILE *file_out;
    file_out = fopen("references-tri-selection7.txt", "w");
    if (file_out == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        free(tab);
        return 1;
    }
    for (int j = 0; j < i; j++) { // Utiliser une variable différente de i pour l'itération
        fprintf(file_out, "%llu\n", tab[j]); // Utilise %llu pour uint64_t
    }
    fclose(file_out);

    //Libération de la mémoire allouée
    free(tab);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 1000000 //13 pour le test

void TriParSelection(uint64_t *tab, int n){ //utilisation de pointeurs + uuint64_t car sinon, tri mal fait (références trop longues)
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

int main()
{
    //Ouverture du fichier d'entrée
    FILE *file_in;
    file_in = fopen("references.txt", "r"); //"references-test.txt" pour le test avec 13 références. 
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
    while (fscanf(file_in, "%llu", &tab[i]) != EOF && i < SIZE) { // Utilise %llu pour uint64_t au lieu de %d
        i++;
    }
    fclose(file_in);

    // Tri par sélection du tableau
    TriParSelection(tab, SIZE);

    // Écriture du tableau trié dans le fichier de sortie
    FILE *file_out;
    file_out = fopen("references-tri-selection.txt", "w");
    if (file_out == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        free(tab);
        return 1;
    }
    for (int i = 0; i < SIZE; i++) {
        fprintf(file_out, "%llu \n", tab[i]); // Utilise %llu pour uint64_t
        //printf("%llu \n", tab[i]); pour écrire les valeurs dans la console pour vérifier quand sur linux
    }
    fclose(file_out);

    //Libération de la mémoire allouée
    free(tab);

    return 0;
}


#!/bin/bash

# Chemin du fichier d'entrée
input_file="references-test.txt"
# Chemin du fichier de sortie
output_file="references-tri-selection.txt"

# Lire le fichier et stocker les valeurs dans un tableau
mapfile -t references < "$input_file"

# Fonction de tri par sélection modifiée pour trier d'abord par nombre de chiffres
tri_selection() {
    local -n arr=$1
    local n=${#arr[@]}
    local min_idx i j

    for ((i=0; i<n-1; i++)); do
        min_idx=$i
        for ((j=i+1; j<n; j++)); do
            # Comparaison d'abord basée sur la longueur des nombres, puis sur leur valeur
            if (( ${#arr[j]} < ${#arr[min_idx]} || (${#arr[j]} == ${#arr[min_idx]} && arr[j] < arr[min_idx]) )); then
                min_idx=$j
            fi
        done
        # Échange des éléments
        tmp=${arr[i]}
        arr[i]=${arr[min_idx]}
        arr[min_idx]=$tmp
    done
}

# Appliquer le tri par sélection
tri_selection references

# Écrire les résultats dans le fichier de sortie
for ref in "${references[@]}"; do
    echo "$ref" >> "$output_file"
done

echo "Le fichier trié a été créé avec succès."

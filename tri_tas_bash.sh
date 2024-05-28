#!/bin/bash

# Chemin du fichier d'entrée
input_file="references-test.txt"
# Chemin du fichier de sortie
output_file="references-tri-tas.txt"

# Lire le fichier et stocker les valeurs dans un tableau
mapfile -t references < "$input_file"

# Fonction pour ajuster le tas
construire_tas() {
    local -n arr=$1
    local n=$2
    local i=$3
    local largest=$i
    local l=$((2 * i + 1))
    local r=$((2 * i + 2))

    # Comparaison basée sur la longueur des nombres, puis sur leur valeur si les longueurs sont égales
    if [[ $l -lt $n && ( ${#arr[$l]} -gt ${#arr[$largest]} || ( ${#arr[$l]} -eq ${#arr[$largest]} && ${arr[$l]} -gt ${arr[$largest]} ) ) ]]; then
        largest=$l
    fi

    if [[ $r -lt $n && ( ${#arr[$r]} -gt ${#arr[$largest]} || ( ${#arr[$r]} -eq ${#arr[$largest]} && ${arr[$r]} -gt ${arr[$largest]} ) ) ]]; then
        largest=$r
    fi

    if [[ $largest != $i ]]; then
        # Échange des éléments
        tmp=${arr[$i]}
        arr[$i]=${arr[$largest]}
        arr[$largest]=$tmp
        construire_tas "$1" $n $largest
    fi
}

# Fonction de tri par tas
tri_par_tas() {
    local -n arr=$1
    local n=${#arr[@]}

    # Construire un tas en tenant compte de la longueur des nombres
    for ((i=n/2-1; i>=0; i--)); do
        construire_tas "$1" $n $i
    done

    # Extraire les éléments du tas
    for ((i=n-1; i>0; i--)); do
        # Échanger l'élément racine avec le dernier élément
        tmp=${arr[0]}
        arr[0]=${arr[$i]}
        arr[$i]=$tmp
        construire_tas "$1" $i 0
    done
}

# Appliquer le tri par tas
tri_par_tas references

# Écrire les résultats dans le fichier de sortie
for ref in "${references[@]}"; do
    echo "$ref" >> "$output_file"
done

echo "Le fichier trié a été créé avec succès."


def construire_tas(arr, n, i):
    largest = i  
    l = 2 * i + 1     
    r = 2 * i + 2    

    if l < n and arr[i] < arr[l]:
        largest = l

    if r < n and arr[largest] < arr[r]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  
        construire_tas(arr, n, largest)

def tri_par_tas(arr):
    n = len(arr)

    # Construire un tas (heapify)
    for i in range(n // 2 - 1, -1, -1):
        construire_tas(arr, n, i)

    # Extraire les éléments un par un du tas
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  
        construire_tas(arr, i, 0)



def main():
    # Lecture de references.txt
    with open('references-test.txt', 'r', encoding='UTF-8') as file:
        references = [int(line.strip()) for line in file]

    tri_par_tas(references)

    # Écriture du fichier trié references-tri-selection.txt
    with open('references-tri-tas-py.txt', 'w') as file:
        for reference in references:
            file.write(str(reference) + '\n')
    
    print("Le fichier trié a été créé avec succès.")

if __name__ == "__main__":
    main()


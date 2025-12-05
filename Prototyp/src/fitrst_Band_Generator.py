from itertools import permutations

def init():
    # Erstellt Permutationen für die zweite Zeile (basierend auf 1-4)
    init_second_rows = [1, 2, 3, 4]
    return permutations(init_second_rows)

def write(second_row):
    # Schreibt das Ergebnis in die Datei first_bands
    full_band = [1, 2, 3, 4] + list(second_row)
    with open("Prototyp/Sudoku_Grids/first_bands.txt", "a") as f:
        f.write(str(full_band) + "\n")
  
def is_valid(second_row):
    
    # Indizes 0-3: Erste Zeile 
    # Indizes 4-7: Zweite Zeile 
    full_grid = [1, 2, 3, 4] + list(second_row)

    # SPALTEN-CHECK 
    for i in range(4):
        if full_grid[i] == full_grid[i+4]:
            return False
 
    # Block 1: Besteht aus Index 0,1 (Zeile 1) und 4,5 (Zeile 2)
    block_1 = {full_grid[0], full_grid[1], full_grid[4], full_grid[5]}
  
    if len(block_1) != 4:
        return False

    # Block 2 (Rechts Oben): Besteht aus Index 2,3 (Zeile 1) und 6,7 (Zeile 2)
    block_2 = {full_grid[2], full_grid[3], full_grid[6], full_grid[7]}
    
    if len(block_2) != 4:
        return False

    
    return True
    
def run():
    second_rows = init()
    for p in second_rows:
        if is_valid(p):
            write(p)

if __name__ == "__main__":
    run()
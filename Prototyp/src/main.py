import sys
from copy import deepcopy

class SudokuGenerator:
    def __init__(self, n=2):
        
        #n=2 wegen (2x2 Blöcken) steht für 4x4 Grid 
        
        self.n = n
        self.size = n * n
        
        self.grid_len = self.size * self.size
        self.unique_hashes = set()
        self.total_found = 0

    def get_empty_grid(self):
        return [0] * self.grid_len

    def index_to_coords(self, index):
        return index // self.size, index % self.size # index ist zwischen 0 bis 15 z.b index=1 -> (0,1)

    def is_valid(self, grid, index, num):
        row, col = self.index_to_coords(index)
        
        # Zeilen-Check
        start_row = row * self.size
        if num in grid[start_row : start_row + self.size]: 
            return False                                 #Falls num schon drinne ist um duplikate zu vermeiden
            
        # Spalten-Check
        if num in grid[col :: self.size]:
            return False                                 #Falls num schon drinne ist um duplikate zu vermeiden

        # Block-Check
        block_row_start = (row // self.n) * self.n       #Um die indizes vom block zu bestimmen bzw. welche gehören zum gleichen Block
        block_col_start = (col // self.n) * self.n
        
        for row in range(self.n):                          #Checkt ob num schon im block vorhanden ist
            for col in range(self.n):
                idx = (block_row_start + row) * self.size + (block_col_start + col)   # row=⌊idx/size⌋,=col=idx%size -> idx=(row)*size + col
                if grid[idx] == num: 
                    return False
        return True


    def solve_all(self, grid, index=0): #Backtracking Algorithmus
        
        if index == self.grid_len:
            # fALLS Lösung gefunden Kopie zurückgeben
            yield list(grid)
            return

        # Wenn Feld schon belegt überspringen
        if grid[index] != 0:
            yield from self.solve_all(grid, index + 1)
            return

        for num in range(1, self.size + 1):
            if self.is_valid(grid, index, num):  
                grid[index] = num
                yield from self.solve_all(grid, index + 1)
                grid[index] = 0  # Backtrack


    def to_tuple(self, grid):  #Weil man in einem Set keine Listen speichern darf und tuple immutable sind
        return tuple(grid)  

    def relabel_to_min(self, grid):  
        """
        Relabeling: Mappe die Zahlen so um, dass die Sequenz
        lexikographisch minimal wird.
        Beispiel: Ein Grid [2, 1, 3...] wird zu [1, 2, 3...].
        """
        mapping = {}
        next_num = 1
        new_grid = []
        for num in grid:
            if num not in mapping:
                mapping[num] = next_num
                next_num += 1
            new_grid.append(mapping[num])
        return tuple(new_grid)

    
    def rotate_90(self, grid): #Rotiert das Grid 90° nach rechts
        new_grid = [0] * self.grid_len
        for r in range(self.size):
            for c in range(self.size):
                # (r, c) wird zu (c, size - 1 - r)
                old_idx = r * self.size + c
                new_idx = c * self.size + (self.size - 1 - r)
                new_grid[new_idx] = grid[old_idx]
        return new_grid

    
    def mirror(self, grid): #Spiegelt das Grid an der Diagonalen
        new_grid = [0] * self.grid_len
        for r in range(self.size):
            for c in range(self.size):
                new_grid[c * self.size + r] = grid[r * self.size + c]
        return new_grid
    

    def band_swaps():  #Band-Swaps müssen noch gemacht werden
        return


    def get_canonical_form(self, grid): 

        variations = []
        
        current = list(grid)

        # Mit (4 Rotationen * 2 Spiegelungen) werden alle 8 varianten erzeugt
        for _ in range(4): # Wegen 4 Rotationen
            # Normal
            variations.append(self.relabel_to_min(current))

            variations.append(self.relabel_to_min(self.mirror(current)))
            
            # Weiterdrehen für nächsten Loop
            current = self.rotate_90(current)
            
        # Nimm das "kleinste" Tupel als Repräsentant für die klasse
        return min(variations)
            
    def save_to_file(self, filename="sudokus.txt"):
        
        #Schreibt alle gefundenen Unikate in eine Textdatei.
        
        print(f"Schreibe {len(self.unique_hashes)} Sudokus in '{filename}'...")
        
        try:
            with open(filename, "w") as f:
                for grid_tuple in self.unique_hashes:
                    line = "".join(str(num) for num in grid_tuple)
                    f.write(line + "\n")
            print("gespeichert")
            
        except IOError as e:
            print(f"Fehler beim Schreiben der Datei: {e}")

    def run(self):
        print("Starte Generierung für 4x4 Sudokus")
        
        empty = self.get_empty_grid()
        
        for solution in self.solve_all(empty):
            self.total_found += 1
            
            # Berechne die  Kanonische Form
            canonical = self.get_canonical_form(solution)
            
            #Wenn die kannonosiche Form nicht im Set ist hinzufügen
            if canonical not in self.unique_hashes:
                self.unique_hashes.add(canonical)

        print("-" * 30)
        print(f"Sudokus generiert: {self.total_found}")
        print(f"Essentially different Sudokus: {len(self.unique_hashes)}")

        self.save_to_file(f"Essentially_Diffrent_{self.size}x{self.size}.txt")

if __name__ == "__main__":
    gen = SudokuGenerator(n=2) 
    gen.run()
import sys
from copy import deepcopy

class Sudoku4x4py:
    def __init__(self):
        self.n = 2          # Blockgröße
        self.size = 4       # Gridgröße
        self.count_ed = 0   # ed:Essentially Different

    def get_empty_grid(self): #init ein leeres grid
        return [0] * 16

    def is_valid(self, grid, index, num): #Prüft ob man num auf diesen index packen darf
        row = index // 4
        col = index % 4
        
        # Zeile prüfen
        start_row = row * 4
        if num in grid[start_row : start_row + 4]: return False
        
        # Spalte prüfen
        if num in grid[col :: 4]: return False
        
        # 2x2 Block prüfen
        block_row = (row // 2) * 2
        block_col = (col // 2) * 2
        for r in range(2):
            for c in range(2):
                idx = (block_row + r) * 4 + (block_col + c)
                if grid[idx] == num: return False
        return True

    def solve(self, grid, index=0, callback=None): #Backtracking zum solven des Sudokus
        if index == 16:
            if callback: callback(list(grid))
            return

        if grid[index] != 0:
            self.solve(grid, index + 1, callback)
            return

        for num in range(1, 5):
            if self.is_valid(grid, index, num):
                grid[index] = num
                self.solve(grid, index + 1, callback)
                grid[index] = 0 # Reset

    
    def rotate(self, grid):
        """Dreht 90 Grad im Uhrzeigersinn"""
        new_grid = [0] * 16
        for r in range(4):
            for c in range(4):
                new_idx = c * 4 + (3 - r)
                old_idx = r * 4 + c
                new_grid[new_idx] = grid[old_idx]
        return new_grid

    def mirror(self, grid):
        """Spiegelt an der Diagonalen"""
        new_grid = [0] * 16
        for r in range(4):
            for c in range(4):
                new_grid[c * 4 + r] = grid[r * 4 + c]
        return new_grid

    def relabel(self, grid):  
        mapping = {}
        next_num = 1
        new_grid = []
        for num in grid:
            if num not in mapping:
                mapping[num] = next_num
                next_num += 1
            new_grid.append(mapping[num])
        return tuple(new_grid) # Tuple für Vergleichbarkeit

    """
        Prüft: Ist 'grid' das lexikografisch kleinste (MinLex) 
        aller seiner geometrischen Variationen?
        """
    def is_canonical(self, grid):
        
        original_minlex = self.relabel(grid)
        
        current = list(grid)
        
        # Wir prüfen alle 8 Symmetrien (4 Rotationen * 2 Spiegelungen)
        for _ in range(4):
            # 1. Prüfe aktuelle Rotation
            variant = self.relabel(current)
            if variant < original_minlex:
                return False # Wir haben eine kleinere Variante gefunden -> Original ist kein MinLex!

            # 2. Prüfe Spiegelung der aktuellen Rotation
            mirrored = self.mirror(current)
            variant_mirror = self.relabel(mirrored)
            if variant_mirror < original_minlex:
                return False 

            # Weiterdrehen
            current = self.rotate(current)
            
        return True

    
    def run(self):
        print("Generiere 4x4 Essentially Different Sudokus...")
        
       # Setzen Zeile 1 fest auf [1, 2, 3, 4]
        grid = self.get_empty_grid()
        grid[0:4] = [1, 2, 3, 4]
        
        #Starte den Solver erst ab Zeile 2
        self.solve(grid, index=4, callback=self.process_solution)
        
        print(f"\n Anzahl Essentially Different Sudokus: {self.count_ed}")

    def process_solution(self, grid):
        if self.is_canonical(grid):
            self.count_ed += 1
            # Ausgabe (String Format)
            s = "".join(str(x) for x in grid)
            print(f"ED Nr. {self.count_ed}: {s}")
           

if __name__ == "__main__":
    app = Sudoku4x4py()
    app.run()
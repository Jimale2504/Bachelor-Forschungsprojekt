import sys
import ast 
from copy import deepcopy

class Sudoku4x4py:
    def __init__(self):
        self.n = 2          # Blockgröße
        self.size = 4       # Gridgröße
        self.count_ed = 0   # ed: Essentially Different
        self.output_file = "Prototyp/Sudoku_Grids/ED_Sudokus.txt"
        self.input_file = "Prototyp/Sudoku_Grids/first_bands.txt" # Pfad zur Datei mit den 1 Bands

    def get_empty_grid(self): 
        return [0] * 16

    def is_valid(self, grid, index, num): 
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

    def solve(self, grid, index, outfile): #Backtracking Algorithmus 
        # Wenn wir über das letzte Feld hinaus sind, ist das Grid voll
        if index == 16:
            self.process_solution(list(grid), outfile)
            return

        # Wenn Feld schon belegt (durch Start-Band), überspringen
        if grid[index] != 0:
            self.solve(grid, index + 1, outfile)
            return

        for num in range(1, 5):
            if self.is_valid(grid, index, num):
                grid[index] = num
                self.solve(grid, index + 1, outfile)
                grid[index] = 0 # Backtracking Reset

    '''Symmetrie Operationen'''

    def rotate(self, grid): #Dreht das Grid 90° im Uhrzeigersinn
        
        new_grid = [0] * 16
        for r in range(4):
            for c in range(4):
                new_idx = c * 4 + (3 - r)
                old_idx = r * 4 + c
                new_grid[new_idx] = grid[old_idx]
        return new_grid

    def mirror(self, grid): #Spiegelt an der Diagonalen

        new_grid = [0] * 16
        for r in range(4):
            for c in range(4):
                new_grid[c * 4 + r] = grid[r * 4 + c]
        return new_grid

    def relabel(self, grid):  
        """
        Benennt die Zahlen um, sodass die erste gefundene Zahl 1 ist, die zweite 2, etc.
        Macht das Grid vergleichbar unabhängig von den konkreten Zahlenwerten.
        """
        mapping = {}
        next_num = 1
        new_grid = []
        for num in grid:
            if num not in mapping:
                mapping[num] = next_num
                next_num += 1
            new_grid.append(mapping[num])
        return tuple(new_grid) # Tuple für Vergleichbarkeit

    def is_canonical(self, grid): #MinLex-Prüfung
       
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

            # Weiterdrehen für nächsten Durchlauf
            current = self.rotate(current)
            
        return True

    def process_solution(self, grid, outfile):
        """
        Prüft auf ED-Eigenschaft und schreibt in Datei.
        """
        if self.is_canonical(grid):
            self.count_ed += 1
            # Formatierung als String
            s = str(grid)
            print(f"Gefunden ED Nr. {self.count_ed}: {s}")
            outfile.write(s + "\n")

    def run(self):
        
        try:
            with open(self.input_file, "r") as f_in:
                lines = f_in.readlines()
        except FileNotFoundError:
            print(f"Fehler: Datei '{self.input_file}' nicht gefunden.")
            return

        print(f"Starte Generierung und schreibe in {self.output_file}...")
        
        # Ausgabedatei öffnen 
        with open(self.output_file, "w") as f_out:
            
            # Über alle Bänder aus der Datei iterieren
            for line in lines:
                line = line.strip()
                if not line: continue
                
                try:
                    #"[1, 2, ...]" in Liste umwandeln
                    band = ast.literal_eval(line)
                except:
                    print(f"Warnung: Konnte Zeile nicht lesen: {line}")
                    continue

                if len(band) != 8:
                    print(f"Warnung: Band hat falsche Länge ({len(band)}), überspringe...")
                    continue

               
                grid = self.get_empty_grid()
                grid[0:8] = band # Die ersten 8 Werte setzen
                
                # Solver starten ab Index 8
                # Wir übergeben das File-Handle f_out, damit process_solution schreiben kann
                self.solve(grid, index=8, outfile=f_out)
        
        print(f"\n {self.count_ed} Essentially Different Sudokus gefunden.")
        print(f"Ergebnisse gespeichert in '{self.output_file}'.")

if __name__ == "__main__":
    app = Sudoku4x4py()
    app.run()
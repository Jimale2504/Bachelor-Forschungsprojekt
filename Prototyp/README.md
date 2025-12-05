# 🧩 4x4 **Essentially Different** (ED) Sudoku Generator
Ein Prototyp zur vollständigen Erzeugung aller strukturell einzigartigen 4x4-Sudokus.

Das Ziel dieses Projekts ist es, eine Datenbank aller **wirklich unterschiedlichen** (essentially different, ED) 4x4-Sudokugitter zu erstellen – also Gitter, die sich nicht durch **Rotation**, **Spiegelung** oder **Relabeling** ineinander überführen lassen.

## 📄 **Ein- und Ausgabeformate**
- **Input:** `Sudoku_Grids/first_bands.txt`  
  Startkonfigurationen (erste Bänder) für die Generierung  
- **Output:** `Sudoku_Grids/ED_Sudokus.txt`  
  Liste aller gefundenen ED-Sudokus  

## 🚀 **Ablauf & Algorithmus**
Der Generator arbeitet in drei Phasen:

### 1️⃣ **Input laden**  
Die Startbänder werden aus `first_bands.txt` eingelesen.

### 2️⃣ **Backtracking-Vervollständigung**  
Ein Backtracking-Algorithmus erweitert jedes Startband zu einem vollständigen 4x4-Sudokugitter.

### 3️⃣ **Filterung auf strukturelle Einzigartigkeit**  
Für jedes erzeugte Gitter wird geprüft, ob es seine **MinLex-Repräsentation** ist – also die lexikographisch kleinste Variante unter allen:

- Rotationen  
- Spiegelungen  
- Permutationen der Symbole  

Nur die Unikate werden gespeichert.

## 📂 **Projektstruktur**

```
Prototyp/
├── src/                         # Quellcode
│   ├── 4x4_ED_Sudoku_Generator.py
│   └── first_Band_Generator.py
├── Sudoku_Grids/                # Daten (Input & Output)
│   ├── first_bands.txt          # INPUT: Start-Bänder
│   └── ED_Sudokus.txt           # OUTPUT: Generierte ED-Lösungen
└── README.md
```

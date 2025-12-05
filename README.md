# Bachelor-Forschungsprojekt

## Prototyp
Prototyp welcher alle 4x4 ED Sudokus bestimmt.


## Virtual-catalog-DLL
Dieses Projekt nutzt Code aus **Virtual-catalog-DLL** (GPL‑3.0 lizenziert):  
https://github.com/GPenet/Virtual-catalog-DLL

## 📘 Übersicht

Das Skript **`run.py`** dient als Python‑Wrapper für das C++‑Tool **`sktvcat.exe`**, um *Essentially Different (ED) Sudokus* – also minimal lexikale Lösungen – aus dem virtuellen Katalog zu generieren.

Zusätzlich existiert im Hauptverzeichnis ein **Prototyp**, der unter dem Ordner **`Prototyp/`** zu finden ist.  
Dieser Prototyp generiert 4x4 ED‑Sudokus und dient zur als Test unserer vorangehensweise der ED‑Grid‑Erzeugung.

## ▶️ Nutzung

Die ED‑Sudokus können entweder über `run.py` generiert werden oder man kann direkt den folgenden Konsolenbefehl verwenden:

```bash
sktvcat -c0 -v0-[anfang] -v1-[ende] -v2-1
```

Dabei ersetzt du `anfang` und `ende` durch die jeweiligen Band‑Indizes (zwischen 0 und 415).

**Beispiel:**
```bash
sktvcat -c0 -v0-0 -v1-415
```
Dies gibt alle ED‑Sudokus aus.

Man kann auch ein spezifisches ED‑Grid mit folgendem Befehl generieren (mit dem Index **RANK** von 1 bis 5,472,730,538):

```bash
sktvcat -c1 -v0-[RANK]
```

## 📚 Benötigte Bibliotheken

Folgende DLLs müssen im Verzeichnis vorhanden sein:

* `skbvcminlex.dll`
* `skbminlex.dll`
* `skgminlex.dll`
* `skbgridmin.dll`

## 📁 Projektstruktur

```
Virtual-catalog-DLL/
├── run.py                # Python-Wrapper-Skript
├── sktvcat.exe           # C++ Tool
├── skvcat.dll            # Benötigte DLL
├── skbminlex.dll         # Benötigte DLL
├── ...                   # Weitere DLLs
│

Prototyp/             # ED-Sudoku-Prototyp (ohne DLLs)
    ├── src/
    ├── Sudoku_Grids/
    └── README.md
```

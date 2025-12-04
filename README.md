# Bachelor-Forschungsprojekt
This project uses code from Virtual-catalog-DLL licensed under GPL-3.0.
Virtual-catalog-DLL from https://github.com/GPenet/Virtual-catalog-DLL

Virtual Catalog Wrapper für ED Sudokus (run.py)
Dieses Python-Skript (run.py) dient als Wrapper für das C++ Tool sktvcat.exe, um Essentially Different (ED) Sudokus (minimal lexikale Lösungen) aus dem virtuellen Katalog zu generieren.

Alternativ kann man auch den command sktvcat -c0 -v0-[anfang] -v1-[ende] -v2-1 ausführen (anfang und ende halt mit dem Index der Bänder austauschen)
e.g sktvcat -c0 -v0-0 -v1-415 um alle ED-Sudokus zu printen

📚 Die benötigten Bibliotheken:
-skbvcminlex .dll
-skbminlex.dll
-skgminlex.dll
-skbgridmin.dll

Virtual-catalog-DLL/
├── run.py                # Skript
├── sktvcat.exe           # C++ Tool
├── skvcat.dll            # Benötigte DLL
├── skbminlex.dll         # Benötigte DLL
├── ... (weitere DLLs)
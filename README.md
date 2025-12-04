# Bachelor-Forschungsprojekt

Dieses Projekt nutzt Code aus **Virtual-catalog-DLL** (GPL‑3.0 lizenziert):
[https://github.com/GPenet/Virtual-catalog-DLL](https://github.com/GPenet/Virtual-catalog-DLL)

## 📘 Übersicht

Das Skript **`run.py`** dient als Python‑Wrapper für das C++‑Tool **`sktvcat.exe`**, um *Essentially Different (ED) Sudokus* – also minimal lexikale Lösungen – aus dem virtuellen Katalog zu generieren.

## ▶️ Nutzung

Du kannst ED‑Sudokus entweder über `run.py` generieren oder direkt den folgenden Konsolenbefehl verwenden:

```bash
sktvcat -c0 -v0-[anfang] -v1-[ende] -v2-1
```

Dabei ersetzt du `anfang` und `ende` durch die jeweiligen Band‑Indizes.

**Beispiel:**

```bash
sktvcat -c0 -v0-0 -v1-415
```

Dies gibt alle ED‑Sudokus im angegebenen Bereich aus.

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
```

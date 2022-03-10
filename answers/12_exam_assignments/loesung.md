# Inhalt: Cython: Extension Types and Interfacing With C / C++
 

# Exam Assignments 



## What are extension types in the context of Python?

Extension Types sind performante Klassen die kompiliert wurden.

Diese können direkt in C geschrieben werden wobei dazu die Python API benutzt wird. Mit Cython ist es auch möglich Extension Types zu schreiben, wobei dies mit deutlich weniger Aufwand möglich ist. Bei Extension Types schreibt man Klassen die ähnlich zu Python Klassen sind. Hier werden allerdings zusätzlich die Typen der Attribute gesetzt. Externen Code der in C/C++ geschrieben wurde kann durch die Verwendung von Extension Types gewrapped werden und in Python Programmen verwendet werden. Der Code der dabei entsteht ist deutlich beschleunigt.




## How do extension types data fields in Cython differ from data fields in Python classes?


Datenfelder in einem Cython Erweiterungstyp sind nur zugänglich innerhalb von Cython Code. Um den Zugriff von Python aus zu ermöglichen, müssen wir
die Zugriffsebene für dieses Feld erklären (readonly oder public). Cython Datenfelder müssen im Voraus auf Klassenebene deklariert werden. Wir können auch Felder deklarieren, die selbst Erweiterungstypen sind. Der Zugriff auf Datenfelder in Cython Code ist sehr schnell. In Python Klassen werden die Daten nicht auf Klassenebene deklariert und es werden auch keine Typen für die Daten angegeben. Ein weiterer Unterschied zwischen Datenfeldern in Cython und in Python ist es, dass bei Python Klassen alle Attribute einer Klasse in einem Konstrukt namens __dict__ gespeichert werden. Dieses Konstrukt gibt es bei Cython Datenfeldern nicht. 




## Give a simple description of how to wrap C / C++ code in Cython.

Als Beispiel wird hier das wrappen des C++ Programms der Berechnung von Pi gewählt.  
Das Programm besteht aus einer pi.cpp Datei und der Header Datei pi.h.
Als Eingabeparameter wird die Anzahl an Iterationsschritten "num_steps" angegeben und als Ausgabe erhalten wir den iterativ berechneten Wert von Pi nach "num_steps" vielen Schritten. Zusätzlich wird nun eine .pyx Datei benötigt, um den obigen C++ Code zu wrappen. In der "compute_pi.pyx" Datei befinden sich zu Beginn die Compiler Direktiven. Dabei wird die Sprache der Cython Datei als C++ gewählt und die Quelldatei pi.cpp, die Compiler Flags und das Sprachlevel werden angegeben.
Mittels cdef wird die Schnittstelle zum C++ Programm angegeben, welche hier die Funktion "compute_pi" aus der Headerdatei pi.h ist. Nun wird die Cython Datei mithilfe der Eingabe von "cythonize -i compute_pi.pyx" im Terminal kompiliert. Dies erzeugt automatisch eine C++ Datei und eine .so Datei. Die .so Datei entspricht unserem erzeugten Modul, welches wir in unserem Python Code importieren und verwenden können.


# Inhalt: Cython Introduction
 

# Exam Assignments 



## What is Cython?

Cython ist eine compilierte Sprache, d.h. man schreibt Code in Cython und übersetzt diesen in ein native extension Modul. Dieses Modul kann man dann in Python importieren.  
Cython wird genutzt, um Python Code zu beschleunigen. Die Performance kritischen Teile des Python Codes werden dabei in Cython ausgelagert.
Mit Cython können außerdem Verknüpfungen zu C und C++ Bibliotheken erstellt werden. Das bedeutet Code der in C oder C++ geschrieben wurde kann mithilfe von Cython gewrappet werden und dadurch in Python genutzt werden. Cython ist eine Obermenge von Python. Das bedeutet, dass jeder Python Code auch valider Cython Code ist. Man kann sich Cython als mächtige Programmiersprache vorstellen, welche sowohl C und C++ als auch Python beinhaltet.



## Describe an approach how Python programs can be accelerated with the help of Cython.

Eine Möglichkeit Python Programme mithilfe von Cython zu beschleunigen wurde bereits in der vorherigen Frage genannt. Die Idee ist es, Programmteile, welche in Python eine lange Laufzeit haben in C oder C++ auszulagern und dort schneller zu berechnen.  

Um die komplette Pipeline der Beschleunigung mithilfe von Cython zu verstehen, wird die Berechnung von Pi als Beispiel gewählt. Zu Beginn wird das Python Programm zur Berechnung von Pi in einem Jupyter Notebook geöffnet. Dann erstellt man ein Cython File, d.h. ein File mit der Endung .pyx. In diese Datei kopieren wir unser Python Programm. Das Cython File kann im Terminal mit dem Befehl "cythonize" kompiliert werden. Wenn man das Cython Programm nun startet, stellt man bereits eine Beschleunigung fest. Von Cython wird eine Berichtsdatei erstellt, welche die Stellen im Code markiert, welche optimiert werden können. Um zusätzlichen Speedup zu erreichen werden Typ Annotationen in den Code eingebaut. Für die Variable "num_steps" wird der Typ "unsigned long long" gewählt. Die Variablen "width" und "csum" werden als "double" deklariert. Hierdurch wird ein enormer Speedup erreicht.


## Describe two ways for compiling a .pyx Cython module.

1. Mithilfe des Kommandos cythonize wird eine .py oder .pyx Datei in ein C/C++ File umgewandelt. Die C/C++ Datei wird dann in ein Erweiterungsmodul umgewandelt, welches direkt in Python importiert werden kann.  

2. Eine Alternative für das Compilieren eines .pyx Cython Moduls bietet Jupyter Notebook. Jupyter Notebooks sind web-basierte, interaktive Tools, welche viel von der Machine Learning und Data Science Community genutzt werden. Jupyter Notebooks sind sehr felxibel und gut geeignet für schnelle Tests, Präsentation von Ergebnissen und auch für Lernmaterial. Jupyter Notebook unterstützt Cython. Dazu muss im Jupyter Notebook zuerst die Cython Extension geladen werden. Dies geschieht mit dem Befehl "%load_ext cython". Mithilfe der Eingabe von "%%cython" am Beginn einer Zelle im Jupyter Notebook wird die gesamte Zelle in eine Cython Datei kompiliert. Das konkreten Jupyter Notebook speichert man als .ipynb Datei ab und kann dieses beispielsweise über das Terminal aufrufen. Der Befehl hierfür lautet "jupyter-notebook [name].ipynb". Daraufhin öffnet sich im Web-Browser ein Fenster, in dem das Jupyter Notenook ausgeführt werden kann.  



## Name and describe two compiler directives in Cython.

Compiler-Direktiven sind Anweisungen, die das Verhalten von Cython-Code beeinflussen.  

overflowcheck (True/False):  
Wenn diese Direktive auf True gesetzt ist, werden Fehler bei überlaufenden arithmetischen C-Integer-Operationen ausgelöst. Verursacht einen geringen Laufzeitverlust, ist aber viel schneller als die Verwendung von Python-Integer. Der Default-Wert ist False.

language_level (2/3/3str):  
Legt global die Python-Sprachstufe fest, die für die Modulkompilierung verwendet werden soll. Der Default-Wert ist die Kompatibilität mit Python 2. Um die Semantik von Python 3-Quellcode zu aktivieren, wird der Wert am Anfang eines Moduls auf 3 (oder 3str) gesetzt oder man übergibt die Befehlszeilenoptionen "-3" oder "-3str" an den Compiler. Die Option 3str aktiviert die Python 3-Semantik, ändert aber nicht den Typ str und die nicht vorangestellten String-Literale in Unicode, wenn der kompilierte Code in Python 2.x läuft. Man sollte beachten, dass importierte Dateien diese Einstellung von dem zu kompilierenden Modul erben, es sei denn, es wird explizit eine eigene Sprachstufe gesetzt. Eingebundene Quelldateien erben diese Einstellung immer.



## What is the difference between def, cdef and cpdef when declaring a Cython function?

def Funktion:  
Hierdurch wird eine ganz normale Python Funktionen deklariert. Dabei wird kein Rückgabewert angegeben. 

cdef Funktion:  
Diese Funktion kann nur in Cython verwendet werden. Sie ist sehr schnell und entspricht einer C-Funktion, die verwendet wird. Funktionen die als cdef deklariert werden können nicht von einem python Programm aufgerufen werden. Hier wird der Rückgabewert mit angegeben.


cpdef Funktion:  
Im Hintergrund werden zwei Varianten abspeichert. Eine Python und eine Cython Variante. Je nachdem in welchem Kontext diese Funktion aufgerufen wird, wird entweder die Python oder die Cython Variante verwendet. Auch hier wird ein Rückgabewert mit angegeben.


## What are typed memoryviews especially useful for in Cython?

Mithilfe von typed memoryviews könnnen aus Python numpy Arrays oder auch normale Python Arrays nach Cython übergeben werden. Damit kann effizient auf die Datentypen zugegriffen werden.


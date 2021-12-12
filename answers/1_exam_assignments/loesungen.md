# describe how **parallelism** differs from **concurrency**.

Wir betrachten mehrere Handlungsstränge in einem System. Bei Parallelität laufen mehrere Handlungsstränge zur selben Zeit ab. Parallelität bedeutet hier, dass beispielsweise vier tasks (aufgaben) gleichzeitig von vier CPUs eines Rechners abgearbeitet werden. Das heißt, dass zu einem festen Zeitpunkt mehrere tasks bearbeitet werden. Bei Concurrency (Nebenläufigkeit) werden auch mehrere Handlungstränge betrachtet in denen Aufgaben erledigt werden. Hier werden verschiedene Aufgaben allerdings nicht ausschließlich zur gleichen Zeit abgearbeitet sondern teilweise auch nacheinander. Man kann sich Concurrency so vorstellen, das man nur eine CPU nutzt, welche verschiedene tasks abarbeitet. Zwischen den tasks schaltet die CPU allerdings um und erledigt die tasks nicht zur gleichen zeit, da sie zu einem festen Zeitpunkt immer nur an einem task arbeiten kann. Dabei wird ein sogenannter sheduler verwendet, der zwischen des tasks hin und her schaltet. Hier spricht man auch von einem switch zwischen mehreren tasks. Parallelität ist also eine Teilmenge von Concurreny. Das heißt jedes System, welches parallel ausgeführt wird ist auch concurrent aber nicht jedes system, welches concurrent ausgeführt wird ist auch parallel.

# what is **fork-join parallelism**?

Der fork-join Parallelismus ist das Programmiermodell von OpenMP. Zu Beginn läuft nur der Masterthread. Zu einem bestimmten Zeitpunkt erzeugt dieser Masterthread mehrere Threads, welche für eine bestimmte Zeit parallel zusätzlich zum Masterthread laufen. Diese Abschnitte im Programm werden auch parallele Regionen genannt. Am Ende einer parallelen Region beginnt eine sequenzielle Phase, in welcher ausschließlich der Masterthread weiterläuft. Auf diese sequenzielle Phase kann dann wieder eine parallele Region folgen, welche wieder von einer sequenziellen Phase gefolgt wird. In einer parallelen Region können wiederum parallele Regionen aufgemacht werden. In diesem Fall spricht man von "Nested parallel regions". Dieser Ablauf erinnert an eine Verzweigung (symbolisiert die parallele Region mit mehreren threads), welche durch ein Join wieder zusammengeführt wird. Daher die Bezeichnung "Fork-Join Parallelism".

# **read chapter 1** from Computer Systems: A Programmer's Perspective. Discuss one thing you find interesting.

## Single-Instruction, Multiple-Data (SIMD) Parallelism

SIMD ist Teil der Flynnschen Klassifikation, welche die Rechnerarchitekturen nach der Anzahl ihrer vorhandenen Befehls- und Datenströme unterteilt. Dabei gibt es vier verschiedene Kategorien. SISD (single instruction, single data), SIMD (single instruction, multiple data), MISD (multiple instruction, single data) und MIMD (multiple instruction, multiple data).
Die meisten modernen CPU Architekturen können Vektoroperationen durchführen, welche dem SIMD Prinzip folgen. Das bedeutet, dass eine Operation auf mehrere Daten zur selben Zeit angewendet wird. Dadurch entsteht eine gewisse Parallelität. Ein gutes Beispiel für SIMD Operationen ist die Fused-Multiply-Add (FMA) Anwendung. Dabei betrachtet man die single-precision floating point Operation:

c += a * b

Wenn wir diese Operation sequenziell auf skalaren Daten ausführen müssen wir zwei Instruktionen und somit zwei Zyklen durchführen, wenn wir im Register arbeiten.
Nun seinen a,b und c Vektoren mit beispielsweise zehn Komponenten. Wenn wir die obige Rechnung nach dem SISD Prinzip durchführen, müssen wir zehn Mal zwei, also zwanzig Instruktionen durchführen. Wenn wir allerdings nach dem SIMD Prinzip rechnen können, so bleiben wir bei zwei Instruktionen, da sowohl die Instruktion (a * b) als auch die Zuweisung in die Variable c für jede Komponente der Vektoren gleichzeitig ausgeführt werden kann.
SIMD-fähige Prozessoren werden vorallem bei der Verarbeitung von Bild-, Ton- und Videodaten eingesetzt, da die dort zu verarbeitenden Daten meist hochgradig parallelisierbar sind. 


# read the paper **There's plenty of room at the Top: What will drive computer performance after Moore's law?**. Explain in detail the figure **Performance gains after Moore's law ends.**
Moore's Law beschreibt, dass sich die Anzahl an Transistoren auf einem Computerchip alle zwei Jahre verdoppelt. Durch dieses Gesetz erhält man eine starke Verbessserung der Rechenleistung. Dieses Gesetz hatte lange Zeit Gültigkeit, ist aber mittlweile an ihre physikalsichen Grenzen geraten. Daher spricht man auch von einer post-Moore Ära, in welcher wir uns mittlerweile befinden. Die Verbesserung an Rechenleistung erlagen wir, wie in der Abbildung dargestellt, durch die drei Faktoren Software, Algorithmen und Hardware Architektur. Diese Faktoren befinden sich an der Spitze der Rechnertechnologie ("The Top"). Die Verbesserung der Anzahl der Transistoren pro Computerchip hingegen befinden sich am Boden der Rechnertechnologie ("The Bottom"). Die drei Faktoren werden in der Abbildung bildlich veranschaulicht, beschrieben und mit Beispielen erläutert. Zu Software zählt das "Software perfomance engineering". Darunter versteht man, dass man die Software restrukturiert und effizienter, im Hinblick auf die Laufzeit des Programms, programmiert. Die Software wird an die Hardware des Systems angepasst und die Vorteile von parallelen Prozessen und von Vektorisierungen werden genutzt. Ein weiterer Faktor sind Algorithmen und im speziellen das Nutzen von neuen, besseren Algorithmen, um auch neue Problemstellungen lösen zu können. Der dritte Faktor ist die Hardware Architektur. Hier werden komplexere Prozessor Kerne durch simplere Kerne ersetzt, welche weniger Transistoren benötigen. Diese Modernisierung wird auch als "Hardware streamlining" bezeichnet.


# Coding Warmup

Times from OpenMP versions for integration of pi:

1 thread: pi with 100000000 steps is 3.1415926535904264 in 0.600584 seconds

4 threads: pi with 100000000 steps is 3.1415926535902168 in 0.162669 seconds

8 threads: pi with 100000000 steps is 3.1415926535896137 in 0.0824038 seconds

16 threads: pi with 100000000 steps is 3.1415926535897749 in 0.0724681 seconds

32 threads: pi with 100000000 steps is 3.141592653589774 in 0.0640428 seconds

64 threads: pi with 100000000 steps is 3.141592653589794 in 0.0641696 seconds

--> je mehr threads desto schneller allerdings ist das programm bei 32 und 64 threads etwa gleich schnell. Das heißt ab bestimmter threadanzahl bekommen wir keinen weiteren speedup.


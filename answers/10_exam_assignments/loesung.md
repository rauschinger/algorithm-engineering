# Inhalt: Debugging and Profiling
 

# Exam Assignments 



## Name and explain some useful compiler flags during development.

-Wall  
aktiviert alle Compiler Warnmeldungen.

-g:  
generiert debug Informationen die nützlich für den Debugger und Profiler sind.

-fsanitize=adress:  
Dieser Flag ist ein Gamechanger. Die Flag detektiert out-of-bound Zugriffe, das heißt Zugriffe auf nicht initialiserten Speicher. Außerdem werden use-after-free Zufriffe detektiert. Diese Situation tritt ein, falls Speicher freigegeben wurde und man auf diesen trotzdem zugreift. Hier würde man auf nicht nicht definierten Speicher zugreifen. Außerdem können durch diese Flag memory leaks gefunden werden. Memory Leaks treten auf, wenn Speicher angelegt wurde, dieser aber später nicht deallokiert wurden. Der Compiler zeigt einem dann diese Stellen im Code an.

-fsanitize=undefinded:  
Detektiert undefiniertes Verhalten zur Laufzeit. Typisches undefiniertes Verhalten ist ein Integer Overflow.

Man sollte beachten, dass die Compiler Flags zwischen verschiedenen Compilern verschiedene Bezeichnungen haben. Die oben genannten Flags funktionieren auf dem gcc und clang Compiler, allerdings nicht beim Nutzen des Intel Compilers.


## How could Intel oneAPI help you write better programs?

Das Intel oneAPI Toolkit supportet sowohl CPUs, GPUs FPGAs und andere Beschleuniger. Mit diesem Toolkit können Programme unterschiedlicher Programmiersprachen, wie C++ und Cuda untersucht werden. Das Toolkit enthält unter anderem den Intel Compiler, den Intel Inspector und VTune. Mithilfe des Intel Inspectors lässt sich threading und Speicher Korrektheit prüfen. Im Speziellen können so Deadlocks und Data Races detektiert werden. Vtune hingegen diagnostiziert die gesamten Performance Metriken einer Anwendung. Dabei werden unter anderem die Zyklen pro Instruktion, Gleichzeitigkeit von Threads, die Rate der Cache Misses und die erreichte Speicher Bandbreite betrachtet. Außerdem werden durch den Einsatz von VTune Hotspots des Programms, d.h. die Teile des Programms mit der längsten Laufzeit, detektiert. 



## What can we learn from the following quote? Premature optimization is the root of all evil (Donald Knuth).

Das Zitat besagt, dass man Code nicht blind optimieren sollte. Zuerst sollte man profilen und Messungen durchführen, um Bottlenecks und Hotspots des Codes zu finden. Daraufhin sollte man versuchen die Bottlenecks und Hotspots zu verstehen und diese Stellen zu optimieren.

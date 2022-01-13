# Inhalt: Guided Vectorization and Data Types for Vector Intrinsics  

# Notes  




# Exam Assignments  


## Explain three vectorization clauses of your choice that can be used with #pragma omp simd.  

#pragma omp simd:  

Wenn man sicher ist, dass die for schleife vektorisierbar ist sollte dieses pragrma gesetzt werden. Das heißt in der for schleife dürfen keine Datenabhängigkeiten zwischen den Iterationen auftauchen. In der Schleife dürfen auch keine breaks oder continues auftauchen. Wenn man in einem For-Loop Datenabhängigkeiten hat, ist es eine Möglichkeit den For-Loop auf zwei unabhängige For-Loops aufzuteilen. Dies ist die einfachste Form eine For-Schleife mittels OpenMP und der simd Klausel zu vektorisieren.  
Den speedup den man durch den einsatz von verschiedenen pragmas erhält ist comiler- und betriebssystem abhängig. Mit dem Einsatz von pragmas erzeugt man zwar portablen code aber der code ist nicht performance portabel.  

1. Klausel: aligned  

Syntax: #pragma omp simd aligned(a,b,c:64):  
aligned(a,b,c:64) bedeutet, dass man dem Compiler sagt, dass die Variablen a,b und c 64 byte aligned sind. Dabei müssen a,b und c Pointer auf die Speicheradressen der Variablen sein. Dem Compiler wird gesagt, dass die genutzten Variablen, bzw. pointer oder auch Arrays aligned sind zu einer bestimmten byte boundary. Dabei nimmt man meist 64 byte, da dies der Größe einer cacheline entspricht.  
Wenn die aligned Klausel benutzt wird, sollten die Elemente im Speicher auch aligned sein. Das heißt beim Anlegen der Variablen sollten diese auch in der gewünschten byte größe aligned sein, sonst erhält man durch die aligned Klausel bei dem gcc compiler keinen speedup und das Programm kann Fehlermeldungen werfen.  

2. Klausel: safelen  

Syntax: #pragma omp simd safelen(n):  
Die safelen Klausel setzt ein Limit für die Vektorlänge, wobei n die maximale Länge des Vektors ist. safelen(32) bedeutet, dass der For-Loop für Vektoren der Länge 32 sicher vektorisiert werden kann. Der Unterschied zwischen der safelen und simdlen Klausel ist, dass die safelen clausel für die Korrektheit des Codes notwendig ist, wobei die simdlen Klausel nur eine Empfehlung ist, nicht notwendig umgesetzt werden muss und auch von den meisten Compilern ignoriert wird.  

3. Klausel: reduction  

Syntax: #pragma omp simd reduction(reduction-identifier:list)  
Diese Klausel führt eine Reduktion auf jeder Variable in "list" bezüglich der Operation "reduction-identifier" aus. Als Reduktionsoperation sind die Operationen +, -, *, &, |, ^, && und || zulässig. In einer Anwendung könnte die Klausel wie folgt aussehen:  
#pragma omp simd reduction(* : list)  
hier werden alle Elemente in "list" mittels * zu einem Wert reduziert.  
Bei der reduction Klausel sollte beachtet werden, dass die Operationen min und max mittels OpenMP und der Reduktionsklausel nicht vektorisiert werden können. Das Problem ist, dass die Instruktionen nicht von allen Architekturen (SSE, AVX,..) unterstützt werden. Beispielsweise können bei den AVX2 Instruktionen min und max nicht mit 64 bit integer typen berechnet werden. Die min und max Operationen kann man allerdings selber vektorisiert implementieren.  




## Give reasons that speak for and against vectorization with intrinsics compared to guided vectorization with OpenMP.  

vorteile und nachteile nennen  

vektorisierbarer code kann in manchen fällen nicht vom compiler automatisch vektorisiert werden. Hier hilft der Einsatz von vector intrinsics. Der Programmierer legt selbst im Programm fest, welche Vektorgrößen und Vektorinstuktionen verwendet werden und wie die Daten in die Vektoren aus dem Speicher geladen werden. Man steuert selbst die Vektorisierung. Beispielsweise können compiler Sortieralgorithmen nicht von alleine vektorisieren. Hier hilft der Einsatz von vector intrinsics. Der große Nachteil von vecotor intrinsics ist, das es spezifische intrinsics Datentypen und Funktionen für einzelne Prozessorarchitekturen gibt. Das heißt mit dem Vorteil der Performance Portabilität bekommt man einen Verlust der Code Portabilität. Wenn der Compiler Code vektorisieren kann, ist die Vektorisierung mit OpenMP einfacher umzusetzen. Dabei müssen lediglich die passenden pragmas gesetzt werden und Informationen beispielsweise über das alignment sollten an den Compiler weitergegeben werden. Der Compiler übernimmt dann die Arbeit der Vektorisierung für den Programmierer.  


## What are the advantages of vector intrinsics over assembly code?  

für vector intrinsics argumentieren  

Im Vergleich zu assembly code sind vector instrinsics einfacher zu lernen und einfacher zu programmieren. Bei vector intrinsics entsteht ein besser lesbarer code. Außerdem sind intrinsics portabler zwischen unterschiedlichen compilern und operating systems, da die vecotr intrinsics C++ Code sind. Bei assembly kann sich der code zwischen verschiedenen compilern und operating systems unterscheiden. Ein weiterer Grund für den Einsatz von vector intrinsics im Vergleich zu assembly code ist, dass die vector intrinsics wrapper um assembly Instruktionen sind. In einem wrapper können mehrere assembly Instruktionen hintereinander geschaltet werden, was zu einer starken Vereinfachung führt. Vector intrinsics haben den Vorteil, dass die exiplizite Zuweisung von Registern nicht notwendig ist. Bei Assembly muss bei Operationen mit Vektoren konkret angegeben werden aus welchem Register die Vektoren geladen werden. Dies entfällt bei vector intrinsics.  




## What are the corresponding vectors of the three intrinsic data types: __m256, __m256d and __m256i.  

__m256: vektor mit 8 32-bit float zahlen  

__m256d: vektor mit 4 64-bit double zahlen  

__m256i: vektor mit signierten oder unsignierten integer zahlen  

Beachte: bei _256i weiß man nicht welche Form von integer-werten in dem vektor steht. Die operation mit dem vektore entscheidet, welche form von integer-werten in dem vektor steht. Möglich sind hier beispielsweise 16 16-bit short zahlen, 8 32-bit integer zahlen oder 4 64-bit long zahlen.  




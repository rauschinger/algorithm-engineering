# Inhalt: Vector Intrinsics and Instruction-Level Parallelism  
 

# Exam Assignments 


## Explain the naming conventions for intrinsic functions. (< vector_size >,< operation >, < suffix >)

< vector_size >:  
< vector_size > spezifiziert die Größe des zurückgegebenen Vektors. Dabei steht mm für 128-bit Vektoren was dem SSE Vektorinstruktionssatz entspricht, mm256 für 256-bit Vektoren wie im AVX oder AVX2 Vektorinstruktionssatz. mm512 steht für 512-bit Vektoren, welche im AVX-512 Vektorinstruktionssatz vor kommen.

< operation >:
Diese Namenskonvention beschreibt die Operation, welche von der intrinsischen Funktion ausgeführt wird. Beispiele für Operationen sind add (addieren), sub (subtrahieren), mul (multiplizieren), fmadd (Fused-Multply-Add).

< suffix >:
< suffix > gibt den Datentyp von den ersten Argumenten der Funktion an. Dies entspricht dem Datentyp des Input-Vektors. Dabei steht ps für float, pd für double und ep< int_type > für integer Datentypen. epi32 steht beispielsweise für signierte 32-bit integer Werte und epu16 für unsignierte 16-bit integer Werte.

Ein Beispiel für die Anwendung dieser Namenskonvention ist die folgende Fused-Multply-Add Operation:  
__m256 _mm256_fmadd_ps (__m256 a, __m256 b, __m256 c)  
Hier werden die oben beschriebenen Bezeichnungen mm256,fmadd und ps verwendet.


## What do the metrics latency and throughput tell you about the performance of an intrinsic function?


## How do modern processors realize instruction-level parallelism?

Mehrere Instruktionen werden gelichzeitig laufen gelassen auf unterschiedlichen functional units. Unter instruction-level parallelism wird auch superscalar verstanden, was bedeutet, dass mehrere Instruktionen pro Taktzyklus möglich sind. Umgesetzt wird der Instruktion-level Parallelismus also durch die Verwendung von mehreren functional units. Außerdem wird in den CPUs nach den Prinzipien "out of order", "branch prediction" und "speculative execution" gearbeitet. Das heißt es wird versucht voraus zu sagen, welche branches im Code ausgeführt werden und diese werden dann spekulativ ausgeführt. Falls ein branch keine Verwendung findet, wird die geleistet Arbeit verworfen. Im Falle korrekter Vorhersage kann so bereits vorgearbeitet werden. Dabei ist es das Ziel, dass sich die CPUs nicht in einem idle Zustand befinden (das heißt auf Arbeit warten), sondern beschäftigt sind. 



## How may loop unrolling affect the execution time of compiled code?



## What does a high IPC value (instructions per cycle) mean in terms of the performance of an algorithm?

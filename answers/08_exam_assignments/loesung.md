# Inhalt: Vector Intrinsics and Instruction-Level Parallelism  
 

# Exam Assignments 


## Explain the naming conventions for intrinsic functions. (< vector_size >,< operation >, < suffix >)

< vector_size >:  
< vector_size > spezifiziert die Größe des zurückgegebenen Vektors. Dabei steht mm für 128-bit Vektoren was dem SSE Vektorinstruktionssatz entspricht, mm256 für 256-bit Vektoren wie im AVX oder AVX2 Vektorinstruktionssatz. mm512 steht für 512-bit Vektoren, welche im AVX-512 Vektorinstruktionssatz vor kommen.

< operation >:
Diese Namenskonvention beschreibt die Operation, welche von der intrinsischen Funktion ausgeführt wird. Beispiele für Operationen sind add (addieren), sub (subtrahieren), mul (multiplizieren).

< suffix >:
< suffix > gibt den Datentyp von den ersten Argumenten der Funktion an. Dies entspricht dem Datentyp des Input-Vektors. Dabei steht ps für float, pd für double und ep< int_type > für integer Datentypen. epi32 steht beispielsweise für signierte 32-bit integer Werte und epu16 für unsignierte 16-bit integer Werte.


## What do the metrics latency and throughput tell you about the performance of an intrinsic function?


## How do modern processors realize instruction-level parallelism?


## How may loop unrolling affect the execution time of compiled code?



## What does a high IPC value (instructions per cycle) mean in terms of the performance of an algorithm?

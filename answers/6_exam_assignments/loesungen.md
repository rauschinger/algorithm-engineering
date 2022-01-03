# Inhalt: Auto Vectorization  

bisher: bei parallelisierung wird ganzes in teile aufgeteilt und die einzelnen teile berechnen parallel ihre arbeit  

nun vektorisierung: ist auch parallelisierung aber auf datenebene und nicht mittles threads. Anstatt mit skalaren operationen zu arbeiten, arbeiten wir mit vektorinstuktionen. Z.B vektor mit zahlen auf anderen vektor mit zahlen addieren und das mittels einer instruktion. Moderne CPUs haben verschiedene Vektorinstuktionen. Schauen uns in zukünftigen Vorlesungen an, wie man Vektorinstuktionen mittels intrinsischen Funktionen (intrinsics) ansprechen kann.  

hier erste von 3 vorlesungen zu vektorisierung; schauen uns an wie compiler unseren code automatisch vektorisieren kann.  

SIMD (single instruction-multiple data);  
mainstream vektor instruktionen im cpu bereich seit 1998;  
Vektorinstruktionssätze auf Intel CPUs:     
    SSE - SSE4.2 (128 bit; 1999-2009; xmm0 - xmm15), AVX, AVX2 (256 bit; 2011, 2013, ymm0 - ymm15), AVX-512 (512 bit; 2017; zmm0 - zmm31)  
    beispiel:  
    AVX-512 kann mit Vektoren der größe 512 bit rechnen, d.h. 16 floats oder 8 doubles innerhalb eines vektor speichern  
        --> 1 float = 4 byte = 32 bit und 16*32 = 512  
        --> 1 double = 8 byte = 64 bit und 8*64 = 512  
    zu AVX2: ymm0 - ymm15 hier werden vektorregister angesprochen; 0-15 heißt es werden 16 Register angesprochen; x für 128 bit, y für 256 bit und z für 512 bit.  
    die instruktionen sind rückwärtskompatibel, d.h. Code der AVX2 oder SSE verwendet kann auf AVX-512 CPUs laufen; wenn man AVX2 instruktionen auf einer AVX-512 CPU verwendet, nutzt man nicht das komplette register.  
    Am meisten verbreitet ist AVX2.  
Wir wollen hier nur schauen dass der compiler selber die besten instruktionen nutzt. Oben Hintergrundwissen.  
Wie Vektorisieren wir?  
    --> nutzen von libraries ( MKL, OpenBLAS, numpy, Open CV)  
    --> auf guten compiler hoffen und setzen von passenden compiler flags wie  
        -march=native (höchster Vektorinstruktionssatz wird genutzt; ist abwägung zwischen portabilität und performance),  
        -Ofast, -ffast-math (vorsicht bei float semantik im programm; verwendung nicht möglich wenn rundungsfehler eine rolle spielen)  
    --> compiler durch annotations helfen, wie #pragma omp simd. Dadurch entsteht portabler code aber nicht performance portabler code.  
    --> intrinsics und assembly code schreiben. Dadurch erhält man performance portablen code, d.h die performance ist unabhängig vom compiler.  









# Name some characteristics of the instructions sets: SSE, AVX(2) and AVX-512.


# How can memory aliasing affect performance?


# What are the advantages of unit stride (stride-1) memory access compared to accessing memory with larger strides (for example, stride-8)?


# When would you prefer arranging records in memory as a Structure of Arrays?

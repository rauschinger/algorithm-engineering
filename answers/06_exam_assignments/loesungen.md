# Inhalt: Auto Vectorization  

# Notes  

## indroduction  

bisher: bei parallelisierung wird ganzes in teile aufgeteilt und die einzelnen teile berechnen parallel ihre arbeit.    
nun vektorisierung: ist auch parallelisierung aber auf datenebene und nicht mittles threads. Anstatt mit skalaren operationen zu arbeiten, arbeiten wir mit vektorinstuktionen. Z.B vektor mit zahlen auf anderen vektor mit zahlen addieren und das mittels einer instruktion. Moderne CPUs haben verschiedene Vektorinstuktionen. Schauen uns in kommenden Vorlesungen u.a. an, wie man Vektorinstuktionen mittels intrinsischen Funktionen (intrinsics) ansprechen kann.  
In dieser ersten von 3 vorlesungen zu vektorisierung schauen wir uns an wie der compiler unseren code automatisch vektorisieren kann.  
Wie Vektorisieren wir?  
    --> nutzen von libraries ( MKL, OpenBLAS, numpy, Open CV)   
    --> auf guten compiler hoffen und setzen von passenden compiler flags wie  
        -march=native (höchster Vektorinstruktionssatz wird genutzt; ist abwägung zwischen portabilität und performance)    
        -Ofast, -ffast-math (vorsicht bei float semantik im programm; verwendung nicht möglich wenn rundungsfehler eine rolle spielen)  
        Problematik hier: bei unterschiedlichen compilern (intel compiler, gcc, clang,..) kann code teilweise vektorisiert oder auch nicht vektrorisiert werde.   
    --> compiler durch annotations helfen, wie #pragma omp simd. Dadurch entsteht portabler code aber nicht performance portabler code.    
    --> intrinsics und assembly code schreiben. Dadurch erhält man performance portablen code, d.h die performance ist unabhängig vom compiler.   
https://godbolt.org/ : Tool, um zu prüfen ob für einen Code Vektorregister verwendet wurden. Zu eingegebenem code wird der assembler code erzeugt.  

## Array of Structures (AoS) vs Structure of Arrays (SoA)  

Wie legt man objekte sequenziell im speicher an? --> zwei möglichkeiten: Array of Structures (AoS) oder Structure of Arrays (SoA)  
Beispiel: Wir legen in einem Array ganz viele Objekte an, welche jeweils die attribute x,y und z haben.  

Variante AoS: Wir machen ein Array und die Elemente im Array sind die einzelnen Strukturen = Objekte. Das heißt alle Objekte mit ihren Elementen werden nacheinander in einem langen array abgespeichert. Wenn man nun ein bestimmtes element (zB x) von allen objekten haben will, brauchen wir einen strided zugriff, welcher größer stride-1 ist. Dann werden die x Werte aller Objekte in einem vektor abgespeichert.  

Variante SoA: Wir machen eine Struktur und diese eine Struktur hat drei riesen lange arrays. Einen Array für x Werte, einen Array für y Werte und einen Array für z Werte. Wenn wir nun die x werte aller objekte haben wollen, bekommen wir diese durch einen stride-1 zugriff. Wenn man auf alle x Werte der Objekte zugreifen möchte haben wir einen schnelleren Zugriff. Bei SoA ist ein Objekt verstreut im Speicher, da sich die einzelnen Elemente eines Objekts in verschiedenen Arrays im speicher befindet.  

Welche Variante schneller ist hängt vom algorithmus ab.  

https://en.wikipedia.org/wiki/AoS_and_SoA  


## Speicher Alignment  

Wir haben gesehen dass code oft schneller ist, wenn die zu ladenden daten zusammenhängend im speicher sind. Zusätzlich kann der Speicher aligned werden. Bei einem x86-64 prozessor ist es sinnvoll ein 64-byte alignement auf arrays zu haben. Wenn man einen vektor auf zwei verschiedene cache lines aufteilt (bei unaligned) dann müssen zwei cache lines geladen werden. Wenn wir den speicher alignen dann befindet sich in einer cache line immer ein 64 byte vektor.  




# Exam Assignments  

## Name some characteristics of the instructions sets: SSE, AVX(2) and AVX-512.  
  

SIMD (single instruction-multiple data) entspricht Vektorinstuktion. Mainstream Vektorinstruktionen gibt es im cpu bereich seit 1998.  
Es gibt folgende Vektorinstruktionssätze auf Intel CPUs:  
SSE - SSE4.2 (128 bit; 1999-2009; xmm0 - xmm15), AVX, AVX2 (256 bit; 2011, 2013, ymm0 - ymm15), AVX-512 (512 bit; 2017; zmm0 - zmm31)   
Beispiel:  
AVX-512 kann mit Vektoren der größe 512 bit rechnen, d.h. 16 floats oder 8 doubles innerhalb eines vektor speichern.  
    --> 1 float = 4 byte = 32 bit und 16*32 = 512  
    --> 1 double = 8 byte = 64 bit und 8*64 = 512  
Die Namen der Register die für die Instruktionen verwendet werden sind bei der SSE-SSE4.2 xmm0-xmm15, bei AVX, AVX2 ymm0 - ymm15 und bei AVX-512 zmm0 - zmm31. xmm0-xmm15 heißt es werden 16 Register angesprochen. Das x bei xmm0 - xmm15 von dem SSE Vektorinstuktionssatz steht für 128 bit, y bei AVX und AVX2 für 256 bit und z bei AVX-512 für 512 bit.  
Die Instruktionen sind rückwärtskompatibel, d.h. Code der AVX2 oder SSE verwendet kann auf AVX-512 CPUs laufen. Wenn man AVX2 Instruktionen auf einer AVX-512 CPU verwendet, nutzt man nicht das komplette Register. Am weitesten verbreitet ist AVX2.  
Wir wollen hier nur schauen dass der compiler selber die besten Instruktionen nutzt.  


## How can memory aliasing affect performance?  

Unter Pointer Aliasing oder auch Memory Aliasing versteht man den Fall, dass zwei Pointer an die selbe Speicheradresse zeigen. Tritt dieser Fall ein so wird die Performance des Codes schlechter.  
Wenn an einer Funktion zwei pointer übergeben werden weiß man nicht ob die pointer an dieselbe Stelle weißen. Das heißt der compiler weiß nicht ob die pointer überlappende Speicherregionen haben. Daher nimmt der compiler immer an das sich Speicherbereiche von pointern überlappen. Falls man weiß, dass sich bestimmte Speicherbereiche nicht überschneiden so kann man dies dem compiler mitteilen. Dies geschieht mithilfe von einem restricted-keyword. Dadurch kann der compiler performanteren code produzieren. Das gilt nicht nur für pointer sondern auch für Referenzen.  
Wenn man mehrere pointer oder Referenzen hat, welche einer Funktion übergeben werden und man sich sicher ist dass die Speicherbereiche nicht überlappen, dann kann man die pointer/referenzen restricten. Das heißt es muss ein restict-Keyword gesetzt werden.  


## What are the advantages of unit stride (stride-1) memory access compared to accessing memory with larger strides (for example, stride-8)?  

Daten aus dem Arbeitsspeicher werden als cache lines geladen. Eine cache line ist 64 byte groß. Eine bestimmte Bandbreite kann aus dem Arbeitssspeicher geladen werden. Diese Bandbreite möchten wir komplett auslasten. Wenn wir die Bandbreite nicht komplett auslasten können bottlenecks auftreten. Wenn jedes Element aus der geladenen cache line auch genutzt wird, so können die Daten direkt verarbeitet werden. Wenn man stride-8 verwendet, also nur jedes 8te element verwendet, nutzt man die 7 dazwischenm liegenden Elemente nicht. Das heißt die komplette Bandbreite wird nicht genutzt.  

Wenn der code nicht strided ist kann es sein, dass der compiler den code nicht vektorisieren kann. Daher sollte man strided 1 nutzen, denn dann wird die komplette Bandbreite genutzt und der compiler kann den code besser automatisch vektorisieren.  


## When would you prefer arranging records in memory as a Structure of Arrays?  

Wenn man von einem objekt (z.B. einem array) das maximum/minimum/durchschnittswert berechnen möchte lohnt sich ein SoA Ansatz. Bei spalten-orientierten Datenbanken lässt sich so pro Spalte das maximum/minimum/durchschnittswert sehr einfach berechnen. Hier haben wir immer den strided-1 zugriff und können somit eine höhere Bandbreite ausnutzen. In einem festen Zeitraunm werden somit mehr Daten verarbeiten als bei einem strided-4 oder strided-8 Zugriff. Außerdem kann der compiler den code besser vektorisieren. SoA wird nicht bevorzugt, wenn ein Algorithmus genutzt wird welcher immer komplette Objekte aus dem Speicher haben möchte, da sich die objekte auf mehrere arrays aufteilen und bei einer Ausgabe erst zusammen geführt werden müssen. Ob SoA oder AoS die bessere Wahl ist, hängt vom konkret durchgeführten Algorithmus ab.  






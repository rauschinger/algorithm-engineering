# How does the ordered clause in OpenMP work in conjunction with a parallel for loop?

Die ordered Klausel muss beim Start der parallelen Region mit angegeben werden. Dies könnte beispielsweise wie folgt aussehen:   
#pragma omp parallel for ordered schedule (static, 4)   
Außerdem muss an einer Stelle der parallelen Region die geordnete Region mittels   
#pragma omp ordered   
eingeleitet werden. Der Code in der geordneten Region wird sequenziell ausgeführt wie im seriellen Fall. Vor und nach der geordneten Region werden die Threads parallel ausgeführt. 









# What is the collapse clause in OpenMP good for?

Mit der collapse clause kann man verschachtelte For-Schleifen parallelisieren. Wir betrachten zwei verschachtelte For-Schleifen in einer parallelen Region. Die äußere Schleife hat 10 Schleifendurchläufe und die Innere hat 15 Schleifendurchläufe. Ohne die collapse Klausel würde nur die äußere Schleife parallelisiert werden, d.h auf verschiedene Threads aufgeteilt werden. Wenn wir eine CPU mit 32 Hardwarethreads zur Verfügung haben, dann könnte diese Hardware nicht vollständig ausgenutzt werden, da nur 10 Arbeitspakete verteilt werden können. Mit der collapse Klausel erhalten wir eine Schleife mit 10*15 = 150 Schleifendurchläufen. Diese können dann auf die 32 Hardwarethreads verteilt werden.   
Durch den Einsatz der collapse Klausel kann also bei einer kurzen äußeren Schleife die Arbeitslast besser aufgeteilt und parallelisiert werden.

Beispiel:   

#pragma omp parallel for collapse(2)   
  for (int i = 0; i < N; i++) {   
    for (int j = 0; j < M; j++) {   
      // do useful work with i and j   
    }   
  }   


# Explain how reductions work internally in OpenMP.

Das Vorgehen von reduction in OpenMP ist so wie wir es per Hand machen würden. 
Es werden lokale Kopien jeder Variable der Liste in den Threads erstellt. Die Reduktion wird auf den lokalen Kopien ausgeführt. Die Reduktion muss je nach Operation passend initialisert werden. Ist die Operation die Addition, so wird die Reduktion mit 0 initialsiert. Ist die Operation die Multiplikation, so wird die Reduktion mit 1 initialsiert. Wenn die Reduktionen auf den lokalen Kopien abgeschlossen sind, wird das Ergebnis der lokalen Kopien zu einem Wert reduziert, entsprechend der angewendeten Operation. Dieser Wert wird dann in einer globalen Variable abgespeichert.   
Beispiele für Reduktionsoperationen sind Addition, Subtraktion, Multiplikation, Minums- und Maximumsbestimmung. Bei der Reduktion werden dann viele Werte auf einen Wert entsprechend der Operation reduziert.





# What is the purpose of a barrier in parallel computing?

Das Ziel ist es Threads zu synchronisieren.










# Explain the differences between the library routines omp_get_num_threads(), omp_get_num_procs() and omp_get_max_threads().










# Clarify how the storage attributes private and firstprivate differ from each other.












# Do the coding warmup on slide 18. Write in pseudo code how the computation of π can be parallelized with simple threads.


pi beispiel kann mit reduction in einer zeile parallelisiert werden



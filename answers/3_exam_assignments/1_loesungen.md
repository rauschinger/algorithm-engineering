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

Syntax: #pragma omp barrier

Das Ziel ist es Threads zu synchronisieren. Wenn in der parallelen Region eine Barriere gesetzt wurde, dann müssen alle Threads an dieser Barriere warten bis jeder Thread die Barriere erreicht hat. Erst wenn alle Threads die Barriere erreicht haben fahren die Threads mit ihrer Arbeit fort.    
Außerdem gibt es in OpenMP implizite Barrieren. Dazu zählen die for, sections, single und parallel Konstrukte. Bei diesen Kontrukten muss die barrier Direktive nicht mit angegeben werden, da sie implizit in diesen Konstrukten angewendet wird. Beispielsweise arbeiten die Threads bei einer for-Schleife erst dann weiter, wenn alle Threads ihre Arbeit in der for-Schleife abgearbeitet haben. Diese impliziten Barrieren können mithilfe der "nowait" Klausel aufgehoben werden. Das ist allerdings nicht bei dem Konstrukt "parallel" möglich.





# Explain the differences between the library routines omp_get_num_threads(), omp_get_num_procs() and omp_get_max_threads().

omp_get_num_threads(): Diese Routine gibt an, wie viele Threads in der parallelen Region arbeiten, in welcher die Routine aufgerufen wurde. Führt man omp_get_num_threads() außerhalb einer parallelen Region aus, so wird 1 zurückgegeben. Dies entspricht dem Fork-Join-Parallelismus von OpenMP. 


omp_get_num_procs(): Diese Routine gibt die Anzahl der zur Verfügung stehenden logischen Kerne zurück. Logische Kerne unterscheiden sich von physischen Kernen. Wenn wir 4 physische Kerne zur Verfügung haben und die Technology des Hyperthreading nutzen können, dann verhält sich ein physischer Kern wie zwei logische Kerne. Somit haben wir in diesem Fall bei 4 physichen Kernen 8 logische Kerne. Als Default-Wert wird ein Thread pro logischem Kern gestartet.


omp_get_max_threads(): Diese Routine gibt die maximale Anzahl der Threads in einer parallelen Region zurück. Das heißt, dass diese Routine den Wert zurück gibt, welchen man durch die Routine omp_set_num_threads(int) gesetzt hat oder sie gibt den Wert zurück, welcher von der Hardware maximal möglich ist. Hat man beispielsweiße einen Rechner mit 16 Kernen mit Hyperthreading, dann würde omp_get_max_threads() 32 zurückgeben.



# Clarify how the storage attributes private and firstprivate differ from each other.


Variablen die außerhalb einer parallelen Region deklariert werden sind per default shared Variablen. Mithilfe von storage Attributen kann gesteuert werden wie die Variablen, die außerhalb der parallelen Region angelegt wurden, in einer parallelen Region behandelt werden. Dabei gibt es die drei storage Attribute shared, private und firstprivate. Shared ist der default-Wert und bedeutet, dass die Variable von den verschiedenen Threads geteilt wird. Gibt man einer Variable das Attribut privat, so wird eine nicht-initialsierte Kopie der Variable für jeden Thread erstellt. Jeder Thread arbeitet dann auf seiner nicht-initialisierten Kopie der Variable. Da der Wert der Variable nicht-initialsiert ist, ist der Wert der Variable in der parallelen Region für jeden Thread in vielen Fällen 0, könnte aber auch eine zufällige Zahl sein.


Wird eine Variable mit dem firstprivate Attribut versehen, so erhält jeder Thread eine initialiserte Kopie der Variable. Für jeden Thread ist die Variable lokal und eine Kopie der ursprünglichen Variable. Das heißt jeder Thread hat eine Kopie der Variable mit dem Wert den die Variable außerhalb der parallen Region hat und erhält nicht den Wert 0 oder einen zufälligen Wert, wie im Fall des Attributs privat.


# Do the coding warmup on slide 18. Write in pseudo code how the computation of π can be parallelized with simple threads.


pi beispiel kann mit reduction in einer zeile parallelisiert werden



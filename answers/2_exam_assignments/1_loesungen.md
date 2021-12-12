# What causes false sharing?

Eine CPU kann nicht nur ein bestimmtes Byte aus dem Hauptspeicher laden, sondern muss immer die Cache Line laden, in welcher das gewünschte Byte liegt. Eine Cache Line hat typischerweise 64 Byte. Somit werden in diesem Fall mehr Daten geladen als eigentlich benötigt werden. Ein Rechner hat in der Regel mehrere CPUs zur Verfügung. False Sharing tritt ein, wenn threads von unterschiedlichen CPUs verschiedene Variablen einer Cache Line modifizieren. Dadurch wird die Cache Line invalide, woraufhin die Cache Line überall in den caches geupdated wird. Der Speicherupdate wird durch das cache coherency Protokoll sichergestellt. Das Updaten kostet Zeit und verlangsamt den Zugriff auf Variablen der Cache Line durch andere CPUs, welche die Cache Line geladen haben.

Beispiel:
In der Cache Line (CL_1) des Hauptspeichers liegen die Variablen x_1, x_2, ..., x_16. Wir betrachten zwei CPUs, CPU_1 und CPU_2. Beide CPUs holen sich die CL_1. Die CPU_1 benötigt x_5 und die CPU_2 benötigt x_12. Nun betrachten wir folgenden Fall:
CPU_1 modifiziert x_5.
-> Die Cache Line wird für die CPU_2 invalide und muss erst geupdated werden bevor die CPU_2 auf x_12 zugreifen kann.
-> Problem: die CPU_2 benötigt x_5 nicht und muss ihre geladene Cache Line CL_1 trotzdem updaten. Dies kostet Zeit.

In diesem Beispiel tritt das False Sharing also auf, weil sich CPU_ 1 und CPU_2 die Cache Line CL_1 teilen. Das Teilen der Cache Line ist hier nicht erforderlich und gründet auf einer ineffizienten Programmierweise. Es ist besser wenn möglichst viele Variablen einer Cache Line von einer CPU genutzt werden.
False Sharing ist besonders dann zu vermeiden, wenn sehr oft auf die geteilte Cache Line schreibend zugegriffen wird. 

# How do mutual exclusion constructs prevent raceconditions?

Um diese Frage zu beantworten wird zuerst erklärt, was raceconditions sind und was mutal exclusion (mutex) bedeutet.
Eine Race Condition tritt ein, wenn zwei oder mehr treads geteilte Daten zur gleichen Zeit verändern wollen. Wenn beispielsweise x eine geteilte Variable ist und Thread 1 und Thread 2 gleichzeitig die Variable x verändern wollen, so ist nicht definiert, wie x nach diesem gleichzeitgen schreibenden Zugriff aussieht.
Mutual Exclusion ist eine Form der Synchronisation, in welcher nur ein Thread zu einem festen Zeitpunkt einen Codeblock ausführt. Das bedeutet auch dass zu einem festen Zeitpunkt nur ein Thread auf eine Variable zugreifen kann. Dies entspricht einem exklusiven Zugriff eines Threads auf eine Variable.
Wenn wir also ein solches mutial exclusion Konstukt verwenden können raceconditions nicht eintreten, da wir immer einen exklusiven Zugriff auf Variablen haben.
Bei OpenMP verwendet man das mutual exclusion Konstrukt "#pragma omp critical" welches eine Sektion eröffnet, in welcher der Code nur von einem thread zu einem Zeitpunkt ausgeführt wird. Zu den mutual exclusion constructs zählen außerdem der C++ mutex "std::mutex" und die OpenMP Direktive "#pragma omp atomic".
Wenn ein Thread ein mutual exclusion Kontrukt erreicht, so wartet der Thread bis er exklusiven Zugang zu dem Bereich bekommt und durchläuft ihn dann alleine. Wenn also voher ein anderer Thread im exklusiven Bereich ist, so müssen sich threads die auch in diesen Bereich wollen wie in einer Warteschlange anstellen, bis Ihnen der exklusive Zugriff gewährt wird.


# Explain the differences between static and dynamic schedules in OpenMP.

Programmbeispiel: Es werden 50 Bilddateien eingelesen und diese sollen mit einer noise reduktion von 5 threads bearbeitet werden.

Beispiel für einen statischen scheduler in OpenMP:
#pragma omp parallel for schedule (static [,chunk])
Hier werden die abzuarbeitenden Pakete zur Kompilierzeit gleichmäßig auf die threads aufgeteilt unabhängig vom Workload pro Arbeitspaket. Wenn man 5 Threads nutzt so werden bei diesem Programmbeispiel jedem Thread 10 Bilder zugeteilt unabhängig vom Aufwand pro Bild. Den statischen scheduler sollte man verwenden, wenn jeder Loop der for-Schleife ungefähr den gleichen Workload hat.

Beispiel für einen dynamischen scheduler in OpenMP:
#pragma omp parallel for schedule (dynamic [,chunk])
Hier holen sich die threads zur Laufzeit die Bilder aus der for-schleife. Das heißt, wenn ein Thread frei ist holt sich dieser ein neues Bild und bearbeitet es. Dies hat vorallem Vorteile, wenn der Workload unausgeglichen ist. In diesem Programmbeispiel muss ein Thread also nicht zwangsweiße 10 Bilder bearbeiten, sondern kann mehr oder weniger Bilder bearbeiten.

Zusätzlich kann man für in den eckigen Klammer [] angeben, wie viele Elemente aus der For-Schleife bei der Zuteilung auf die Threads mitgegeben werden sollen. Wählt man beispielsweise [2], so werden bei dem statischen scheduler die ersten zwei Bilder auf den ersten Thread verteilt, das zweite und dritte Bild auf den zweiten Thread und so weiter. Das heißt der erste Thread erhält dann beim statischen scheduler außerdem das 11, 12, 21, 22, 31, 32, 41 und 42ste Bild. Beim dynamischen Scheduler werden einem Thread auch immer 2 Bilder zugewiesen, allerdings hängt die Zuweisung welche der Bilder bearbeitet werden vom Workload und somit davon ab, ob der Thread wieder frei ist. 
Der Default Wert beim static scheduler entspricht der gleichmäßigen Aufteilung der Threads, ist also in diesem Programmbeispiel [10]. Der Default Wert beim dynamischen Scheduler ist [1].




# What can we do if we’ve found a solution while running a parallel for loop in OpenMP, but still have many iterations left?

Die Idee ist es aus der parallelen Region herauszuspringen.
Dazu wird eine eine shared variable als flag benutzt, welche den Wert true oder false haben kann. Wenn diese auf einen bestimmten Wert, z.B. auf true gesetzt wird, dann läuft der parallele For Loop zwar weiter aber arbeitet nichts mehr ab. Das heißt die Arbeit im parallelen Loop wird ab einer bestimmten Stelle auf 0 gesetzt (d.h. in den Loops wird keine Arbeit verrichtet), woraufhin der Loop sehr schnell bis zum Ende iteriert. Dies wird durch die Anweisung "continue" erreicht. 



# Do the coding warmup on slide 22. Explain in your own words how std::atomic::compare_exchange_weak work.

## Coding Warmup

3. Das Muster wird erzeugt bei dem schedule: schedule (static, 21).

4. Wenn man den scheduler auf static abändert, liefert das Programm immer den kleinsten Wert. Alternativ siehe continue_hack_min_solution_lock oder continue_hack_min_solution_atomic.cpp.

5. Explain in your own words how std::atomic::compare_exchange_weak work.
Die Eingabewerte für die atomare Funktion std::atomic::compare_exchange_weak lauten (T& expected, T desired).
Diese Funktion kann auf einer atomare Variable aufgerufen werden. Der Funktion wird die Variable "expected" als Referenz übergeben, d.h. innerhalb der Operation kann diese Variable atomar verändert werden. Außerdem wird eine weitere Variable, hier "desired" genannt übergeben, welche die Variable überschreibt auf die die Funktion angewendet wird.
Wir betrachten die Anwendung der Funktion auf die Variable var1:
var1.compare_exchange_weak lauten (T& expected, T desired)
Wenn wir diese Funktion anwenden, wird der Wert der Variable var1 auf welche die Funktion angewendet wird verglichen mit dem Wert der Variable "expected". Wenn die Werte übereinstimmen, so wird var1 mit dem Wert in desired überschrieben und true zurück gegeben. Wenn die Werte nicht übereinstimmen, so wird der Wert von "expected" mit dem Wert von var1 überschrieben und false zurück gegeben.




# Rewrite the parallel program for estimating π from the last exercise to use the construct #pragma omp for.

Siehe pi_openmp_v2.cpp



# Explain how divide and conquer algorithms can be parallelized with tasks in OpenMP.

Tasks sind unabhängige Arbeitspakete. Die Tasks werden in einer Warteschlange abgelegt und dynamisch von den threads aus der Warteschlange entnommen. Die Tasks werden aus der Warteschlange solange entnommen bis die sie leer ist. Da die Tasks unabhängig voneinenader sind, können sie sehr gut parallel abgearbeitet werden.
Bei divide and conquer Algorithmen wird das ursprüngliche Problem in jedem Schritt weiter aufgeteilt. Ein dadurch entstandener Teilbereich kann dann als Task gewählt werden, welcher parallel abgearbeitet wird.   
In OpenMP werden Tasks in einem single Konstrukt erstellt, wodurch sichergestellt wird, dass jeder Task nur einmal generiert wird.    
Ein Beispiel für einen divide and conquer Algorithmus ist der Merge Sort Algorithmus. Dieser Algorithmus sortiert die Elemente eines Arrays. Zuerst wird der Array in der Divide-Phase in mehreren Schritten aufgeteilt. Im ersten Schritt wird der zu sortierende Array in der Mitte geteilt und in zwei Teilarrays abgespeichert. Dieser Schritt wird für jeden Teilarray solange wiederholt, bis man nur noch einelementige Teilarrays hat, welche per Definition sortiert sind. Wie genau die Tasks hier zur Parallelisierung verwendet werden habe ich in der kommenden Frage der Exam Assignments erläutert.



# Describe some ways to speed up merge sort.

merge sort ist ein rekursiver divide and conquer Algorithmus, welcher mittels tasks in OpenMP beschleunigt werden kann.    
In der naiven Version des merge sort Algorithmus wird für jedes Element ein Heap angelegt, d.h wenn zwei Listen gemerged wurden wurde diese Liste auf dem Heap angelegt. Da es teurer ist Speicher auf dem Heap zu allozieren als auf dem Stack, wird der Code so geändert, dass für kleine Arrays nur Speicher auf dem Stack alloziert wird. Kleine Arrays sind hier Arrays mit weniger als 8192 Elementen. Um Speicher dem Stack zuzuweisen wird die Funktion alloca() verwendet.    
Eine weitere Möglichkeit den Merge Sort Algorithmus zu beschleunigen ist es für kleine Arrays nicht den Merge Sort Algorithmus zu verwenden, sondern ein anderes Sortierverfahren zu wählen. Hier wird das Insertion Sort Verfahren für Arrays mit weniger als 32 Elementen verwendet. Für kleine Arrays ist dieser Algorithmus deutlich schneller, da die Stärke des Merge Sort Algorithmus durch eine tiefe Rekursion erst bei großen Arrays zur Geltung kommt.    
Um den Merge Sort Algorithmus weiter zu beschleunigen wird der Algorithmus parallelisiert. Dazu wird die Hilfsfunktion "merge_sort_run()" erstellt. In dieser Funktion wird eine parallele Region aufgemacht. Innerhalb dieser parallelen Region gibt es ein Single Konstrukt, in welchem der Code nur von einem Thread ausgeführt wird. In dem Single Konstrukt wird merge_sort einmal aufgerufen. Die Idee ist es in der Funktion merge_sort() Tasks zu erzeugen, welche in einer Warteschlange eingereiht werden. Die Threads in der parallelen Region holen sich die Tasks aus der Warteschlange und arbeiten sie ab. Die Tasks können auch rekursiv erzeugt werden, d.h. innerhalb eines Tasks können weitere Tasks erstellt werden.   
Auf diese Weise werden in jedem "divide" Schritt des Merge Sort Algorithmus zwei Tasks für die jeweiligen Teillisten erstellt. Die Tasks werden allerdings nur so lange erstellt, bis die Größe der Arrays kleiner als 1000 Elemente ist.

Eine weitere Beschleunigung des Algorithmus erhält man, wenn das Programm so umgeschrieben wird, dass man Speicher wiederverwendet. Dazu wird ein Buffer angelegt, welcher so groß ist wie der zu sortierende Array. Dadurch kann man verhindern, dass immer wieder in den Rekursionsschritten Speicher auf dem Heap oder dem Stack alloziert wird. Der Buffer wird immer wieder abwechselnd von zwei verschiedenen rekursiven Aufrufen von merge sort verwendet. 






# What is the idea behind multithreaded merging?

Das Problem bei dem bisherigen Merge Sort Algorithmus war, dass die der "divide" Abschnitt zwar sehr gut parallelsiert werden konnte, der "Merge" Abschnitt konnte bisher allerdings nur single-threaded, d.h. seriell und nicht parallel durchgeführt werden. Der Merge Schritt ist sehr rechenintensiv, daher skaliert der bisherige Algorithmus nicht gut auf vielen Threads. Ziel ist es also nun den Merge Schritt auch bis zu einer bestimmten Tiefe zu parallelisieren.      
Ausgangspunkt des Merging sind zwei sortierte Teilarrays. Von dem größeren Teilarray wird der Median bestimmt, welcher der Wert in der Mitte des Teilarrays ist, da er bereits sortiert ist. Mittels binärer Suche werden nun die Elemente aus dem kleineren Teilarray bestimmt, die kleiner als der Median des größeren Teilarrays sind. Nun können wir rekursiv die Teilarrays der beiden ursprünglichen Teilarrays mergen, welche die Elemente enthalten die kleiner als der Median sind. Um diese beiden Teilarrays zu mergen wird das obige Verfahren analog angewendet. Das heißt von dem größeren Teilarray wird wieder der Median bestimmt, mittels binärer Suche werden alle Elemente des anderen Teilarrays bestimmt, welche kleiner als dieser Median sind und die Teilarrays werden gemergt.     
Das gleiche können wir für die entstandenen Teilarrays machen, welche die Elemente enthalten die größer als der Median sind. Dadurch bekommen wir unabhängige merges, welche in mehreren Threads parallel berechnet werden können.
Der Große Vorteil hier ist, dass der sequenzielle Teil dieses Vorgehens nur die Bestimmung des Medians ist, welcher nur ein Look-Up ist, da der Teilarray sortiert ist und die binäre Suche. Das restliche Vorgehen besteht aus dem weiteren Aufteilen der Arrays auf verschiedene Threads welche dann rekursiv die Arbeit fortsetzen. 

![Alt-Text](C:\Users\rausc\Desktop\algorithm engineering\answers\4_exam_assignments\multithreaded_merging.png)


# Do the coding warmup on slide 17.


# Read What every systems programmer should know about concurrency. https://assets.bitbashing.io/papers/concurrency-primer.pdf Discuss two things you find particularly interesting.




# Inhalt: Cache and Main Memory
 

# Exam Assignments 


## How do bandwidth-bound computations differ from compute-bound computations?

Der Flaschenhals (besser bekannt als bottleneck) von compute-bound computations ist die CPU. Hier wird kaum bis gar nicht auf den Arbeitsspeicher zugegriffen. Die Laufzeit dieser Algorithmen wird von der Leistung der CPU limitiert.  

Der bottleneck von bandwidth-bound computations ist der Speicherzugriff. Bei Algorithmen bei denen wir viele Speicherzugriffe haben und nur sehr wenig Berechnungen sprechen wir von bandwidth-bound computations, da der limitierende Faktor für die Laufzeit der Speicherzugriff ist. Um die Laufzeit dieser Algorithmen zu beschleunigen versucht man den Speicherzugriff zu optimieren.




## Explain why temporal locality and spatial locality can improve program performance.

Programme die den Cache effizient nutzen haben eine gute zeitliche und räumlicher Lokalität von Speicher.  

In einem Programm mit guter zeitliche Lokalität wird eine Stelle im Speicher die einmal referenziert wird, in naher Zukunft wahrscheinlich mehrfach erneut referenziert. Dadurch werden Daten im Speicher öfter erneut verwendet. Dies kann durch Blocking erreicht werden. Eine geladene Cache Line wird erst dann aus dem Cache geworfen, wenn sie nicht mehr benötigt wird.   

Hat ein Programm gute räumlicher Lokalität, so werden wenn ein einzelnes Element aus einer Cache line verwendet wird auch die anderen nahe gelegenen Elemente aus dieser Cache Line in naher Zukunft verwendet. Bei unit stride memory access, werden alle Elemente aus einer Cache Line verwendet und die räumliche Lokalität wird sicher gestellt.

In beiden Fällen wird die Speicherbandbreite weniger in Anspruch genommen, wodurch die Performance des Programms steigt.  



## What are the differences between data-oriented design and object-oriented design?

Bei objektorientiertem Design von Algorithmen wird sich die reale Welt angeschaut und es werden Klassen erstellt die diese reale Welt abbilden. Von den Klassen werden dann Objekte abgeleitet. Dieses Vorgehen ist einfach nachzuvollziehen für den menschlichen Entwickler. 

Bei datenorientiertem Design (DOD) geht man andersherum vor und fragt sich zuerst was bei dem Programm herauskommen soll. Dann überlegt man wie man schnellstmöglich auf das Ergebnis kommt. Das heißt man betrachtet zuerst den Output und das finale Format dieses Outputs und versucht dann den effizientesten Weg zu finden die Input Bytes in die Output Bytes zu transformieren. Beim DOD verwendet man die Daten als "Structure of Arrays". Auf den Arrays können einfacher direkt Berechnungen durchgeführt werden. Außerdem wird versucht einfache Funktionen, wie beispielsweise die Berechnung des Durchschnitts, auf eine größtmögliche Anzahl von Daten anzuwenden. Hier wird die CPU effizient genutzt und es ist einfacher das Programm zu parallelisieren.


## What are streaming stores?

Bei Caches gibt es zwei verschiedene store Operationen. Beim normalen Speichern werden die Daten erst in den L1 cache dann in den L2 cache und danach in den RAM geschrieben. Bei Streaming Stores werden die Daten aus der CPU direkt in den RAM geschrieben, ohne den Umweg über den L1 und L2 Cache.



## Describe a typical cache hierarchy used in Intel CPUs.



## What are cache conflicts?

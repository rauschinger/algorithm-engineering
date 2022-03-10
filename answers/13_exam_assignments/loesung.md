# Inhalt: Designing SSD-Friendly Applications


# Exam Assignments 


## Delimit from each other the following SSD parts: Cells, Pages and Blocks.

Cells:  
In einer SSD werden Bits in Zellen gespeichert. Es gibt verschiedene Arten von Zellen. Single Level Zellen entsprechen einem Bit, Multiple Level Zellen entsprechen zwei Bits, Triple Level Zellen entsprechen drei Bits und
Quad Level Zellen entsprechen vier Bits. Je weniger Bits pro Zelle vorhanden sind, desto höher ist die Performance und Haltbarkeit und desto höher ist der Preis der SSD.


Pages:  
Eine Seite ist die kleinste Einheit einer SSD die gelesen oder geschrieben werden kann. In einer Seite befinden sich mehrere Zellen. Diese Anschauung entspricht der des zuvor in der Veranstaltung besprochenen Cache Models, wo eine Cacheline die kleinstmögliche Einheit ist, die aus dem Cache geladen werden kann. Eine typische Größe einer Seite ist 4KB. Das Lesen einer Seite ist für gewöhnlich schneller als das Schreiben einer Seite. Außerdem kann eine Seite nur einmal geschrieben und somit nicht überschrieben werden. Um eine Seite zu updaten wird der Inhalt der Seite kopiert, modifiziert und auf eine andere Seite geschrieben. Danach wird die ursprüngliche Seite als invalide markiert und bleibt solange als invalide auf der SSD, bis sie gelöscht wird.


Blocks:  
Ein Block ist die kleinste Einheit einer SSD die gelöscht werden kann. Die typische Größe eines Blocks ist 512KB oder 1MB, bzw. 128 oder 256 Seiten.
Die Lösch-Operation hat eine deutlich längere Latenz als die Schreib- oder Leseoperation.


## What is the purpose of garbage collection in SSDs?

Die Garbage Collection fordert veraltete Blöcke zurück, die mehr ungültige Seiten als ein bestimmter Schwellenwert aufweisen. Die zurückgewonnenen Blöcke werden für zukünftige Schreibvorgänge verfügbar. Die Garbage Collection erhöht die "write amplification". Dies entspricht dem Verhältnis zwischen der Anzahl tatsächlich geschriebener Seiten und der eigentlich gewollten Anzahl an geschriebenen Seiten. Ein optimierter Garbage-Collection-Algorithmus reduziert die write amplification und verbessert so die Leistung und Lebensdauer von SSDs.
Die Garbage Collection verschiebt außerdem zusammengehörige Datensegmente so, dass sie nebeneinander liegen und damit schneller geladen werden können. Um die Last der Garbage Collection zu reduzieren, wird bei einigen SSDs weniger Speicher angegeben als tatsächlich vorhandener Speicher auf der SSD.



## What is the purpose of wear leveling in SSDs?

Wear leveling kann mit Verschleißausgleich übersetzt werden. Wear Leveling ist eine Methode zur Verlängerung der Lebensdauer von SSDs.
Wenn ein Block immer wieder gelöscht und beschrieben wird, wird immer ein wenig zusätzliche Ladung gesammelt. Im Laufe der Zeit, wenn sich diese zusätzliche Ladung aufbaut, wird es immer schwieriger, zwischen einer 0 und einer 1 zu unterscheiden und Blöcke bzw. Seiten gehen kaputt.
FTLs (Flash Translation Layers) sorgen dafür, dass die Blöcke gleichmäßig beschrieben und gelöscht werden und nicht immer wieder der gleiche Block verwendet wird. Dieses Verfahren wird als Wear Leveling bezeichnet. 
Es stellt sich die Frage, was mit langlebigen Daten ist, die nicht überschrieben werden? Hier muss der FTL regelmäßig alle Daten aus solchen Blöcken lesen und sie an anderer Stelle neu schreiben, damit der Block wieder zum Schreiben zur Verfügung steht. Dieser Prozess des Verschleißausgleichs erhöht die "write amplification" der SSD und verringert somit die Leistung, da zusätzlicher Input/Output erforderlich ist um sicherzustellen, dass sich alle Blöcke ungefähr gleich schnell abnutzen.


## Tell some interesting things about SSDs with an M.2 form factor.

Alle aktuellen M.2 SSDs für PCIe benutzen NVMe als Protokoll. Hier muss man aber auch auf die Keys achten. Die Festplatten können unterschiedliche Längen haben. Moderne Laptops haben intern M.2 form factor SSDs. Es gibt allerdings auch andere Formen von SSDs.


## What influence do garbage collection and wear leveling have on write amplification of an SSD?


Wie in den vorherigen Fragen bereits ausführlicher erwähnt, erhöhen die garbage collection und das wear leveling die write amplification einer SSD. 


## Discuss three different recommendations for writing code for SSDs.

Programme mit kompakter Datenstruktur sind gut für die SSD. Dies geschieht wenn man Cache effizienten Code schreibt. Außerdem wird bei Code mit kompakten Daten die Bandbreite der SSD effizienter genutzt. Außerdem soll vermieden werden, dass die SSD komplett ausgelastet ist. Wenn die SSD voll ist wird der write amplification Faktor immer größer, was schlecht für die Performance der SSD ist. Außerdem wird die Garbage Collection bei vollen SSDs aufwändiger und benötigt mehr Zeit.

 

## How could the CPU load for IO be reduced?

Eine SSD hat sehr viele Level von Parallelismus. Um diesen internen Parallelismus auszunutzen müssen möglichst viele Threads erzeugt werden. Dies gilt beispielsweise wenn man viele kleine Dateien lesen möchte. Optimal ist   hier die Verwendung von 60-64 Threads.


## How could you solve problems that do not fit in DRAM without major code adjustments?

Man kann die Probleme mithilfe einer SSD lösen, indem anstatt des DRAMs eine SSD mit mehr Speicher als des RAMs verwendet wird. Dies wurde beispielsweise bei einem Projekt realisiert, wo eine BLAS Bibliothek auf einer SSD geschrieben wurde. Dadurch können Machine Learning Aufgaben auf großen Datenmengen auf einer Workstation ausgeführt werden. Somit bildet die SSD eine Alternative zu verteilten Big Data Systemen. 


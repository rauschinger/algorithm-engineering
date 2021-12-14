# Explain how divide and conquer algorithms can be parallelized with tasks in OpenMP.


Tasks sind unabhängige Arbeitspakete. Die Tasks werden in einer Warteschlange abgelegt und dynamisch von den threads aus der Warteschlange entnommen. Die Tasks werden aus der Warteschlange solange entnommen bis die sie leer ist. Da die Tasks unabhängig voneinenader sind, können sie sehr gut parallel abgearbeitet werden.
Bei divide and conquer Algorithmen wird das ursprüngliche Problem in jedem Schritt weiter aufgeteilt. Ein dadurch entstandener Teilbereich kann dann als Task gewählt werden, welcher parallel abgearbeitet wird.

In OpenMP werden Tasks in einem single Konstrukt erstellt, wodurch sichergestellt wird, dass jeder Task nur einmal generiert wird. 




# Describe some ways to speed up merge sort.

merge sort ist ein rekursiver divide and conquer algorithmus, welcher mittels tasks in OpenMP beschleunigt werden.

# What is the idea behind multithreaded merging?

# Do the coding warmup on slide 17.


# Read What every systems programmer should know about concurrency. https://assets.bitbashing.io/papers/concurrency-primer.pdf Discuss two things you find particularly interesting.




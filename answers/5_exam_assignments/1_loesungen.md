# What is CMake?

CMake ist eine Skriptsprache mit welcher man build files erstellen kann. Cmake funktioniert auf Linux, Mac und Windows Betriebssystemen.
CMake baut einem nicht das Projekt, sondern erstellt nur die build files. Die build files, welche ein Projekt bauen, müssen von einem Compiler ausgeführt werden. Für die verschiedenen Integrierten Entwicklungsumgebungen (IDEs) erstellt CMake die build files. Nutzt man einen Linux Compiler, so werden make files erstellt, bei Windows Compilern werden nmake files erstellt. Nutzt man unter Windows einen gcc Compiler, so werden auch make files erzeugt. 
Um ein Projekt zu erstellen, welches CMake nutzt, muss immer eine Datei namens CMakeLists.txt erstellt werden. In einem Projekt können auch mehrere CMakeLists.txt files vorhanden sein, welche sich in verschiedenen Unterordnern des Projekts befinden. Die CMakeLists.txt files in den Unterordnern beschreiben, wie diese Teilkomponenten des Porjekts kompiliert werden sollen.   
Außerdem kann CMake verwendet werden, um Software zu testen mit ctest und um Software zu packen mit cpack (debfiles). CMake kann auch Windows Executables erstellen wie Installationsfiles.

Cmake ist eine kommandobasierte Sprache mit einem Kommando pro Zeile. Diese Kommandos können nicht verschachtelt werden. Außerdem liefern die Kommandos keinen Wert zurück. Alle Variablen in CMake sind Strings.



# What role do targets play in CMake?

In CMake sind Targets die Dinge, die man erstellen möchte wie executables, libraries oder Tests. Man kann sich Targets wie Objekte aus der objektorienterten Programmierung vorstellen. Um diese Objekte zu erstellen gibt es Konstruktoren. Die Konstruktoren in CMake sind add_executable() und add_library(). Die Targets haben Attribute, auch member variablen genannt, und diese können durch member Funktionen verändert werden. Beispiele von Attributen sind sources von Targets, Compilieroptionen (d.h. die Angabe der Flags mit denen das Target erzeugt werden soll), include directories und gelinkte libraries. Die zugehörigen member Funktionen lauten target_sources(), target_compile_options(), target_include_directories() und target_link_libraries(). Den Funktionen muss der Name des Targets, Zugriffsmodifikationen wie private, public, static oder dynamic und das Attribut in den Klammern übergeben werden. 

wie kann man targets mit objektorienterter programmierung vergkeichen?



# How would you proceed to optimize code?

emfehlung nur api funktionen zu testen

von anfang an tests einbauen



vorallem interfaces testen und randfälle

tests mittels cathc 

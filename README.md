# Lotniskowiec-PSiW
program zaliczeniowy na PSiW

## Temat zadania
### Lotniskowiec

Na lotniskowcu lądują i startują samoloty. W tym celu potrzebują
wyłącznego dostępu do pasa. Lotniskowiec może pomieścić pewną ustaloną
liczbę N samolotów. Jeśli samolotów jest mniej niż K (K < N), wówczas
priorytet w dostępie do pasa mają samoloty lądujące.

Cel zadania: synchronizacja samolotów (pas i miejsce na lotniskowcu to
zasoby).

Źródło zadania: Weiss Z., Gruźlewski T.: Programowanie współbieżne i
rozproszone w przykładach i zadaniach. WNT W-wa 1993.

## Algorytm

W pliku main.cpp znajdują się dwie funkcję ladowanie i wylatywanie.
Zapewniają one samodzielny dostęp do pasa dzięki użyciu mutexa dostepDoPasa.

W funkcji main losujemy z jaką funkcją ma być utworzony wątek.
W przypadku wylosowania funkcji wylatywanie losujemy który samolot ma wylecieć z lotniskowca.

## Kompilacja
W celu kompilacji programu należy pobrać plik main.cpp, a następnie w terminalu wpisać poniższą komendę:
g++ main.cpp -o Lotniskowiec -pthread  -Wall

powstały plik Lotniskowiec należy uruchomić komendą:
./Lotniskowiec

Działanie programu należy zakończyć przy pomocy kombinacji Ctrl + c



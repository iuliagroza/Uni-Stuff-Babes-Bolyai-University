
# Redimensionarea imaginilor

*Nota: se pot folosi implementari native sau implementari bazate pe anumite tooluri specifice*

**Exercitiul 1** 

Sa se implementeze rutine pentru marirea unor imagini 2D RGB (din imagine mica in imagine mai mare) folosind metode de interpolare de tip:
- cel mai apropiat vecin
- biliniara
- bicubica \[optional\]

Afisati imaginile rezultate si comparati (vizual) calitatea lor.

Ce se intampla daca se lucreaza cu imagini 3D?


**Exercitiul 2**

Sa se implementeze rutine pentru micsorarea unor imagini (din imagine mare in imagine mai mica) prin efectuarea unei convolutii asupra unei imagini 2D RGB, folosind diferite kernele (Sobel, Prewitt, Gaussian, etc.). Comparati imaginile rezultate in urma filtrarii si analizati sensibilitatea lor la parametrii filtrului (de ex parametrul sigma al filtrului Gaussian).

Ce se intampla daca imaginea de intrare este 3D?

**Exercitiul 3**

Comparati cele 2 posibilitati de redimensionare a unei imagini:
- prin interpolare
- prin mediere (convolutie)


## Задание 1. Генерация и чтение из файлов

1. С помощью igraph сгенерировать графы
   
Эрдеша-Реньи, Барабаши-Альберт, RGG (https://igraph.org/c/doc/igraph-Generators.html#games-randomized-graph-generators, пункты 1-4)

https://igraph.org/c/doc/igraph-Basic.html

https://igraph.org/c/doc/igraph-Generators.html

2. Научиться сохранять графы в файл, читать из файла типа edgelist

https://igraph.org/c/doc/igraph-Foreign.html#igraph_read_graph_edgelist

(подойдут некоторые файлы из https://snap.stanford.edu/data/index.html)

3. Научиться читать mtx файлы (скачиваем из http://sparse.tamu.edu/)

- нужны файлы mmio.h, mmio.c, igraph_mtx_reader.h, igraph_mtx_reader.c

Пример: https://github.com/annapirova/graph_course_2023/blob/main/igraph_examples/src/example_mtx_reader.c

4. Научиться генерировать графы типа R-Mat, генератор https://github.com/farkhor/PaRMAT
- сохранить как edgelist

## Задание 2. SSSP и MST
1. Научиться запускать на python и С igraph алгоритмы SSSP, MST + свой алгоритм. Графы генерировать случайно типа Эрдеша-Реньи / Барабаши-Альберт / RGG / lattice.

2. Сделать визуализацию алгоритмов на python igraph

Общая документация по рисованию и примеры:

https://python.igraph.org/en/stable/tutorials/index.html

https://python.igraph.org/en/stable/visualisation.html


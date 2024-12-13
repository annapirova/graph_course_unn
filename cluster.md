### Настройка окружения
#### Загрузка компилятора intel2023, intelMPI, MKL
``` 
module load gcc-9.5.0
. /common/intel_oneapi/setvars.sh
export OMP_NUM_THREADS=XXXXX
```
#### Загрузка окружения для Galois
``` 
. /common/intel_oneapi/setvars.sh
conda activate /common/home/group/slasolver/soft/Galois/galois_env
export LD_LIBRARY_PATH=/common/home/group/slasolver/soft/Galois/galois_env/lib:$LD_LIBRARY_PATH
```

#### cmake v 3.20
```
export PATH=/common/home/group/slasolver/cmake-3.20.0/bin:$PATH
```

### Папки
- /common/home/group/slasolver/soft/ -- все софты
- /common/home/group/slasolver/matrices -- некоторые матрицы
- /common/home/group/slasolver/soft/Galois/build2 -- сборка Galois многопоточного
- /common/home/group/slasolver/soft/Galois/build2/lonestar/analytics/cpu -- приложения многопоточные
- /common/home/group/slasolver/soft/Galois/lonestar/analytics/distributed -- сборка Galois распределенного, приложения
- /common/home/group/slasolver/soft/Galois/build2/tools/graph-convert -- конвертер

### Примеры запуска Galois
конвертер
```
./graph-convert --edgelist2gr  --edgeType=void /common/home/group/slasolver/matrices/asia_osm.txt asia_osm2.gr
```
BFS
```
OPENMP_NUM_THREADS=8 srun -N 1 -p gpu -t 10 ./bfs-directionopt-cpu --startNode=1 /common/home/group/slasolver/soft/Galois/build2/tools/graph-convert/asia_osm2.gr
```
BFS distributed (2 процесса на 1м узле)
```
GALOIS_DO_NOT_BIND_THREADS=1 srun -N 1 -n 2 -p gpu -t 10 ./bfs-push-dist /common/home/group/slasolver/soft/Galois/build2/tools/graph-convert/asia_osm2.gr -t=1 -startNode=10 -partition=oec --runs=1
```

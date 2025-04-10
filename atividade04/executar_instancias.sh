#!/bin/bash
cd dataset
gcc -o random random.c
./random
cd ..
cd monobloco
./executar_instancias.sh
cd ..
cd multithread
./executar_instancias.sh
cd ..
cd openmp
./executar_instancias.sh
cd ..

#!/bin/bash
gcc -o shakesort shakesort.c
gcc -o mergesort mergesort.c
./shakesort 1024 ../dataset/1024.txt
./mergesort 1024 ../dataset/1024.txt
./shakesort 16384 ../dataset/16384.txt
./mergesort 16384 ../dataset/16384.txt
./shakesort 262144 ../dataset/262144.txt
./mergesort 262144 ../dataset/262144.txt
./shakesort 4194304 ../dataset/4194304.txt
./mergesort 4194304 ../dataset/4194304.txt
./shakesort 67108864 ../dataset/67108864.txt
./mergesort 67108864 ../dataset/67108864.txt
./shakesort 1073741824 ../dataset/1073741824.txt
./mergesort 1073741824 ../dataset/1073741824.txt

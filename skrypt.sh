#!/bin/bash
./Amake 100 100 > dane.txt
./Bmake 100 >wektor.txt
./a.out 100 100 > wynik1.txt
./Amake 500 500 > dane.txt
./Bmake 500 > wektor.txt
./a.out 500 500 > wynik2.txt
./Amake 1000 1000 > dane.txt
./Bmake 1000 > wektor.txt
./a.out 1000 1000 > wynik3.txt
./Amake 2500 2500 > dane.txt
./Bmake 2500 > wektor.txt
./a.out 2500 2500 > wynik4.txt
./Amake 4096 4096 > dane.txt
./Bmake 4096 > wektor.txt
./a.out 4096 4096 > wynik5.txt
./Amake 10000 10000 > dane.txt
./Bmake 10000 > wektor.txt
./a.out 10000 10000 > wynik6.txt

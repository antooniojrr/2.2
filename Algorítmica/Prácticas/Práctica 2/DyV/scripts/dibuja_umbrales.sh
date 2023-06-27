#!/bin/bash

set terminal png
set output 'dyv_umbrales.png'
set xlabel 'UMBRAL'
set ylabel 'Tiempo (Segundos)'
plot 'tiempos_umbrales.dat' using 1:2 with lines title '100000 vacas', 'tiempos_umbrales.dat' using 1:3 with lines title '500000 vacas', 'tiempos_umbrales.dat' using 1:4 with lines title '1000000 vacas'


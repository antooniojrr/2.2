#!/bin/bash

set terminal png
set output 'comparativa2.png'
set xlabel 'Nº de vacas'
set ylabel 'Tiempo (Segundos)'

f(x) = a2*x*x + a1*x + a0
fit f(x) 'tiempos_esp.dat' via a2,a1,a0 
plot 'tiempos.dat' title 'Algoritmo DyV', f(x) title 'Ajuste Específico'


#!/bin/bash

set terminal png
set output 'dyv.png'
set xlabel 'Nº de vacas'
set ylabel 'Tiempo (Segundos)'
plot 'tiempos.dat' with lines title 'Algoritmo DyV'

f(x) = a1*x*log(x) + a0*x
fit f(x) 'tiempos.dat' via a1,a0 
set output 'dyv_hibrido.png'
set xlabel 'Nº de vacas'
set ylabel 'Tiempo (Segundos)'
plot 'tiempos.dat' title 'Algoritmo DyV', f(x) title 'Ajuste'

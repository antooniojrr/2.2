#!/bin/bash

set terminal png
set output 'especifico.png'
set xlabel 'Nº de vacas'
set ylabel 'Tiempo (Segundos)'
plot 'tiempos.dat' with lines title 'Algoritmo Especifico'

f(x) = a2*x*x + a1*x + a0
fit f(x) 'tiempos.dat' via a2,a1,a0 
set output 'especifico_hibrido.png'
set xlabel 'Nº de vacas'
set ylabel 'Tiempo (Segundos)'
plot 'tiempos.dat' title 'Algoritmo Especifico', f(x) title 'Ajuste'
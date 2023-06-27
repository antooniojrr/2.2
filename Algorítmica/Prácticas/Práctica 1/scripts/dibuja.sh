#!/bin/bash
#
# Uso: gnuplot dibuja.sh

f(x) = <función a ajustar>
fit f(x) '<datos>' via <parámetros>
set terminal png

set output 'ajuste.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot '<datos>' title '<título>', f(x) title 'Curva ajustada'

set output 'grafica.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot '<datos1>' with lines title '<título1>', '<datos2>' with lines title '<título2>', '<datos3>'with lines title '<título3>', '<datos4>' with lines title '<título4>'

set output 'seleccion_0.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot 'seleccion_0.dat' using 1:2 with lines title 'Aleatorio', 'seleccion_0.dat' using 1:3 with lines title 'Orden Inverso', 'seleccion_0.dat' using 1:4 with lines title 'Ordenado'


set output 'seleccion_1.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot 'seleccion_1.dat' using 1:2 with lines title 'Aleatorio', 'seleccion_1.dat' using 1:3 with lines title 'Orden Inverso', 'seleccion_1.dat' using 1:4 with lines title 'Ordenado'

set output 'seleccion_2.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot 'seleccion_2.dat' using 1:2 with lines title 'Aleatorio', 'seleccion_2.dat' using 1:3 with lines title 'Orden Inverso', 'seleccion_2.dat' using 1:4 with lines title 'Ordenado'

set output 'seleccion_3.png'
set xlabel "Tamaño"
set ylabel "Tiempo (segundos)"
plot 'seleccion_3.dat' using 1:2 with lines title 'Aleatorio', 'seleccion_3.dat' using 1:3 with lines title 'Orden Inverso', 'seleccion_3.dat' using 1:4 with lines title 'Ordenado'

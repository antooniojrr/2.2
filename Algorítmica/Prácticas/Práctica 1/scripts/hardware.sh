set terminal png
set output 'seleccion_Hardware_2.png'
set xlabel 'Tamanio'
set ylabel 'Tiempo (Segundos)'
plot 'seleccion_0.dat' using 1:2 with lines title 'PC1','seleccionRandom.dat' with lines title 'PC2', 'salida_seleccion_unix.dat' with lines title 'PC3'



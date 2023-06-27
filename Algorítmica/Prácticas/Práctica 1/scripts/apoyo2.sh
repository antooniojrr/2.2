set terminal png
set output 'comparativa2.png'
set xlabel 'Tamaño'
set ylabel 'Tiempo (Segundos)'

f(x) = a1*x*log(x)+a0
fit f(x) 'heapsort_1.dat' using 1:2 via a1,a0

g(x) = b1*x*log(x)+ b0
fit g(x) 'mergesort_1.dat' using 1:2 via b1,b0

k(x) = d1*x*log(x)+d0
fit k(x) 'quicksort_1.dat' using 1:2 via d1,d0

plot 'burbuja_1.dat' using 1:2 with lines title 'Burbuja', 'insercion_1.dat' using 1:2 with lines title 'Insercion', 'seleccion_1.dat' using 1:2 with lines title 'Seleccion',f(x) title 'Ajuste Heapsort', g(x) title 'Ajuste Mergesort', k(x) title 'Ajuste Quicksort'

set terminal png
set output 'comparativa_log.png'
set xlabel 'Tamaño'
set ylabel 'Tiempo (Segundos)'
k(x) = d1*x*log(x)+d0
fit k(x) 'quicksort_1.dat' using 1:2 via d1,d0
plot 'heapsort_1.dat' using 1:2 with lines title 'Heapsort', 'mergesort_12.dat' using 1:2 with lines title 'Mergesort', k(x) title 'Ajuste Quicksort'
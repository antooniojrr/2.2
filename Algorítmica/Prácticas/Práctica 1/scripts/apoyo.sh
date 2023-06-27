set terminal png
set output 'comparativa.png'
set xlabel 'Tamaño'
set ylabel 'Tiempo (Segundos)'

f(x) = a2*x*x + a1*x + a0
fit f(x) 'burbuja_1.dat' using 1:2 via a2,a1,a0

g(x) = b2*x*x + b1*x + b0
fit g(x) 'insercion_1.dat' using 1:2 via b2,b1,b0

h(x) = c2*x*x + c1*x + c0
fit h(x) 'seleccion_1.dat' using 1:2 via c2,c1,c0

k(x) = d1*x*log(x)+d0
fit k(x) 'quicksort_1.dat' using 1:2 via d1,d0

plot 'mergesort_1.dat' using 1:2 with lines title 'Mergesort', 'heapsort_1.dat' using 1:2 with lines title 'Heapsort', f(x) title 'Ajuste Burbuja', g(x) title 'Ajuste Insercion', h(x) title 'Ajuste Seleccion', k(x) title 'Ajuste Quicksort'
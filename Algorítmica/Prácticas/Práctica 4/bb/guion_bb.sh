#!/bin/bash

echo `g++ -O2 generador.cpp -o generador`
echo `g++ -O2 bb_t.cpp -o bb_t`

i=3
while [ "$i" -le 13 ]
do
echo "$i  "
echo "$i  ">>salida_bb.dat;
./generador $i;
./bb_t 1>> salida_bb_comp.dat
i=$(( $i + 1 ))
done

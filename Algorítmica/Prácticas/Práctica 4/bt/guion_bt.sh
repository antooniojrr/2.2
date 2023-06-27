#!/bin/bash

echo `g++ -O2 generador.cpp -o generador`
echo `g++ -O2 bt_t.cpp -o bt_t`

i=3
while [ "$i" -le 13 ]
do
echo "$i ";
./generador $i;
./bt_t 1>> salida_bt_comp.dat
i=$(( $i + 1 ))
done

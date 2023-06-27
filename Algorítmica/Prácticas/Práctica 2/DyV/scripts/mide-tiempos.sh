#!/bin/bash
# Script para tomar tiempos de ejecución con diferentes cantidades de vacas

NUM=100000
GEN=generador
ALG=dyv
DAT=vacas.dat
OUT=tiempos.dat

i=$NUM
LIM=$(( $NUM * 20 ))
rm $OUT
rm $DAT
while [ "$i" -le $LIM ]
do
    printf "$i\t" >> $OUT
    ./$GEN $DAT $i
    ./$ALG $DAT >> $OUT
    printf "\n" >> $OUT
    i=$(( $i + $NUM ))
    rm $DAT
    
done

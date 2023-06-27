#!/bin/bash
# Script para tomar tiempos de ejecución con diferentes umbrales
# USAR SOLO CON dyv_u

NUM=10
GEN=generador
ALG=dyv_u
DAT=vacas.dat
OUT=tiempos_umbrales.dat
VAC1=100000
VAC2=500000
VAC3=1000000

i=$NUM
LIM=$(( $NUM * 20 ))
rm $OUT
rm $DAT
while [ "$i" -le $LIM ]
do

    printf "$i\t" >> $OUT

    ./$GEN $DAT $VAC1
    ./$ALG $i $DAT >> $OUT
    printf "\t" >> $OUT
    ./$GEN $DAT $VAC2
    ./$ALG $i $DAT >> $OUT
    printf "\t" >> $OUT
    ./$GEN $DAT $VAC3
    ./$ALG $i $DAT >> $OUT

    printf "\n" >> $OUT
    i=$(( $i + $NUM ))
    rm $DAT
    
done

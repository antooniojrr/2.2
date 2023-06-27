#!/bin/bash 
#echo "" >> salida.dat
i=50000
while [ "$i" -le 1250000 ]
do
    printf "$i  " >> $2
    ./$1 $i >> $2
    i=$(( $i + 50000 ))
    printf "\n" >> $2
done
      

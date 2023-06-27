#!/bin/bash 

i=<tamaño inicial>
while [ "$i" -le <tamaño final> ]
do
    printf "$i " >> $2
    ./$1 $i >> $2
    i=$(( $i + 5000 ))
    printf "\n" >> $2
done
      

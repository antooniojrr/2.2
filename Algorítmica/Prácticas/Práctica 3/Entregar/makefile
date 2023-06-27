# Nombre archivo: makefile
# Uso: make
# Autores: Antonio Rodríguez, David Kessler y Santiago López

compile: generador generador-pvc voraz pvc1 pvc2 pvc3

generador: ./Generador/generador.cpp
	g++ -O1 -o generador ./Generador/generador.cpp

generador-pvc: ./Generador-pvc/generador-pvc.cpp
	g++ -O1 -o generador-pvc ./Generador/generador.cpp

voraz: ./Voraz/voraz.cpp
	g++ -O1 -o voraz ./Voraz/voraz.cpp

pvc1: ./Pvc1/pvc1.cpp
	g++ -O1 -o pvc1 ./Pvc1/pvc1.cpp

pvc2: ./Pvc2/pvc2.cpp
	g++ -O1 -o pvc2 ./Pvc2/pvc2.cpp

pvc3: ./Pvc3/pvc3.cpp
	g++ -O1 -o pvc3 ./Pvc3/pvc3.cpp

clean:
	rm generador
	rm voraz
	rm generador-pvc
	rm pvc1
	rm pvc2
	rm pvc3
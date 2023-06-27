# Nombre archivo: makefile
# Uso: make
# Autores: Antonio Rodríguez, David Kessler y Santiago López

compile: generador bt bb

generador: ./Generador/generador.cpp
	g++ -O1 -o generador ./Generador/generador.cpp

bt: ./BT/bt.cpp 
	g++ -O1 -o bt ./BT/bt.cpp

bb: ./BB/bb.cpp
	g++ -O1 -o bb ./BB/bb.cpp

clean:
	rm generador
	rm bt
	rm bb
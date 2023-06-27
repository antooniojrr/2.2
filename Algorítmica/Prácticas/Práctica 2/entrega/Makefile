# Nombre archivo: makefile
# Uso: make
# Autores: Antonio Rodríguez, David Kessler y Santiago López

compile: generador dyv especifico

generador: ./Generador/generador.cpp
	g++ -O1 -o generador ./Generador/generador.cpp

dyv: ./Dyv/dyv.cpp
	g++ -O1 -o dyv ./Dyv/dyv.cpp

especifico: ./Especifico/especifico.cpp
	g++ -O1 -o especifico ./Especifico/especifico.cpp

clean:
	rm especifico
	rm generador
	rm dyv

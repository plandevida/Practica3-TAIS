/*
* JuegoOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "JuegoOthello.h"

JuegoOthello::JuegoOthello(Turno JI) : libres(numCols*numFils) {

	turno = JI;
	tablero = new Matriz<Ficha>(numCols, numFils, Jn);
}

JuegoOthello::JuegoOthello(const JuegoOthello& EJ) : JuegoLogT2(EJ) {

	libres = EJ.libres;
}

void JuegoOthello::aplicaJugada(unsigned int c, unsigned int f) throw(EJuego) {

	if (sePuede(c, f) && !ganador) {

		tablero->at(c, f) = turno;
		libres--;
		ganador = conecta3(c, f);

		if (!ganador) turno = cambia(turno);
	}
	else throw EJuego("Jugada incorrecta");
}

bool JuegoOthello::conecta3(unsigned int c, unsigned int f) {
	return (vertical(c, f) || horizontal(c, f) || subeDer(c, f) || subeIzq(c, f));
}

bool JuegoOthello::vertical(unsigned int c, unsigned int f) {
	return tablero->at(c, 0) == turno && tablero->at(c, 1) == turno && tablero->at(c, 2) == turno;
}

bool JuegoOthello::horizontal(unsigned int c, unsigned int f) {
	return tablero->at(0, f) == turno && tablero->at(1, f) == turno && tablero->at(2, f) == turno;
}

bool JuegoOthello::subeDer(unsigned int c, unsigned int f) {
	return tablero->at(0, 2) == turno && tablero->at(1, 1) == turno && tablero->at(2, 0) == turno;
}

bool JuegoOthello::subeIzq(unsigned int c, unsigned int f) {
	return tablero->at(0, 0) == turno && tablero->at(1, 1) == turno && tablero->at(2, 2) == turno;
}
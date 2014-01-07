/*
* JuegoOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "JuegoOthello.h"

JuegoOthello::JuegoOthello(Turno JI) : libres(numCols*numFils-4), hapasado(false) {

	numFichas[0] = 0;
	numFichas[1] = 0;

	turno = JI;
	tablero = new Matriz<Ficha>(numCols, numFils, Jn);
}

JuegoOthello::JuegoOthello(const JuegoOthello& EJ) : JuegoLogT2(EJ) {

	libres = EJ.libres;
	numFichas[0] = EJ.numFichas[0];
	numFichas[1] = EJ.numFichas[1];
}

void JuegoOthello::aplicaJugada(unsigned int c, unsigned int f) throw(EJuego) {

	if (sePuede(c, f) && !ganador) {

		tablero->at(c, f) = turno;
		libres--;

		if ( turno == Jhum )
			numFichas[0]++;
		else if ( turno == Jmaq )
			numFichas[1]++;

		ganador = othello(c, f);

		if (numFichas[0] > numFichas[1]) {
			turno = Jhum;
		}
		else if (numFichas[0] < numFichas[1]) {
			turno = Jmaq;
		}
		else {
			turno = Jn;
		}

		if (!ganador) turno = cambia(turno);
	}
	else throw EJuego("Jugada incorrecta");
}

bool JuegoOthello::othello(unsigned int c, unsigned int f) {
	bool res = false;

	if ( fin() ) {

	}

	return res;
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
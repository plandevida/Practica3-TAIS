/*
* JuegoOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "JuegoOthello.h"

JuegoOthello::JuegoOthello(Turno JI) : libres( ((numCols-1)*numFils) - 4), hapasado(false) {

	numFichas[0] = 0;
	numFichas[1] = 0;

	turno = JI;
	tablero = new Matriz<Ficha>(numCols, numFils, Jn);
}

JuegoOthello::JuegoOthello(const JuegoOthello& EJ) : JuegoLogT2(EJ) {

	libres = EJ.libres;
	numFichas[0] = EJ.numFichas[0];
	numFichas[1] = EJ.numFichas[1];
	hapasado = EJ.hapasado;
}

void JuegoOthello::aplicaJugada(unsigned int c, unsigned int f) throw(EJuego) {

	if (sePuede(c, f) && !ganador) {

		if (c == numCols) {
			setHaPasado(true);
		}
		else {

			setHaPasado(false);

			tablero->at(c, f) = turno;
			libres--;

			if (turno == Jhum)
				numFichas[0]++;
			else if (turno == Jmaq)
				numFichas[1]++;

			ganador = othello(c, f);

			if (compruebaHorizontal(c, f))
				convierteHorizontal(c, f);

			if (compruebaVertical(c, f))
				convierteVertical(c, f);

			if (compruebaDiagonalDer(c, f))
				convierteDiagonalDer(c, f);
			
			if (compruebaDiagonalIzq(c, f))
				convierteDiagonalIzq(c, f);

			if (!ganador) turno = cambia(turno);
		}
	}
	else throw EJuego("Jugada incorrecta");
}

bool JuegoOthello::othello(unsigned int c, unsigned int f) {
	bool res = false;

	if (fin()) {
		res = true;
	}
	else {

		// Se comprueba que no se puede poner en ninguna casilla libre
		for (int col = 0; col < 8; col++) {
			for (int fil = 0; fil < 8; fil++) {

				if (!sePuede(col, fil)) {
					res = true;
				}
				else { // Comprobamos que el contrario tampoco puede poner

					turno = cambia(turno);

					if (!sePuede(col, fil)) {
						res = true;
					}
					else {
						res = false;
					}

					turno = cambia(turno);
				}
			}
		}
	}

	return false;
}

void JuegoOthello::convierteVertical(unsigned int c, unsigned int f) {

	unsigned int fila = f - 2;
	bool infConvertida = false;
	bool supConvertida = false;

	while (enRango(c, fila) && !infConvertida) {

		if (dameCasilla(c, fila) == turno) {

			// Desplazamos una casilla hacia arriba.
			fila++;

			while (fila <= f - 1) {

				tablero->at(c, fila) = turno;

				fila++;

				infConvertida = true;
			}
		}

		fila--;
	}

	fila = f + 2;

	while (enRango(c, fila) && !supConvertida) {

		if (dameCasilla(c, fila) == turno) {

			// Desplazamos una casilla hacia abajo.
			fila--;

			while (fila >= f + 1) {

				tablero->at(c, fila) = turno;

				fila--;

				supConvertida = true;
			}
		}

		fila++;
	}
}

bool JuegoOthello::compruebaVertical(unsigned int c, unsigned int f) const {

	// Válida representa una ficha del color del jugador
	bool validaAr, validaAb = false;

	// Vacía representa una casilla sin ficha
	bool vaciasAr, vaciasAb = false;

	if ((enRango(c, f - 1) && (dameCasilla(c, f - 1) == cambia(turno))) || (enRango(c, f + 1) && (dameCasilla(c, f + 1) == cambia(turno)))) {

		unsigned int filaAr = f - 2;
		unsigned int filaAb = f + 2;

		while (!vaciasAr && !validaAr && enRango(c, filaAr)) {

			if (dameCasilla(c, filaAr) == Jn) {
				vaciasAr = true;
			}
			else {
				if (dameCasilla(c, filaAr) == turno) {
					validaAr = true;
				}
			}

			filaAr++;
		}

		while (!vaciasAb && !validaAb && enRango(c, filaAb)) {

			if (dameCasilla(c, filaAb) == Jn) {
				vaciasAb = true;
			}
			else {
				if (dameCasilla(c, filaAb) == turno) {
					validaAb = true;
				}
			}

			filaAb++;
		}
	}

	return (validaAr && !vaciasAr) || (validaAb && !vaciasAb);
}

void JuegoOthello::convierteHorizontal(unsigned int c, unsigned int f) {

	unsigned int col = c - 2;
	bool izConvertida = false;
	bool drConvertida = false;

	while (enRango(col, f) && !izConvertida) {

		if (dameCasilla(col, f) == turno) {

			// Desplazamos una casilla a la derecha.
			col++;

			while ( col <= c-1 ) {

				tablero->at(col, f) = turno;

				col++;

				izConvertida = true;
			}
		}

		col--;
	}

	col = c + 2;

	while ( enRango(col, f) && !drConvertida) {
		
		if (dameCasilla(col, f) == turno) {

			// Desplazamos una casilla a la izq.
			col--;

			while (col >= c + 1) {

				tablero->at(col, f) = turno;

				col--;

				drConvertida = true;
			}
		}

		col++;
	}
}

bool JuegoOthello::compruebaHorizontal(unsigned int c, unsigned int f) const {
	
	unsigned int ultimaIgual = -1;
	bool hayVacias = false;

	bool iz, dr = false;

	if ( enRango(c-1, f) && dameCasilla(c - 1, f) == cambia(turno)) {
		for (unsigned int i = 0; i < c; i++) {

			if (dameCasilla(i, f) == turno) {
				ultimaIgual = i;
			}
			else if (ultimaIgual != -1 && dameCasilla(i, f) == Jn) {
				hayVacias = true;
			}
		}

		if (!hayVacias && ultimaIgual != -1) {
			iz = true;
		}
	}

	ultimaIgual = -1;
	hayVacias = false;

	if (dameCasilla(c + 1, f) == cambia(turno)) {
		for (unsigned int j = 7; j > c; j--) {

			if (dameCasilla(j, f) == turno) {
				ultimaIgual = j;
			}
			else if (ultimaIgual != -1 && dameCasilla(j, f) == Jn) {
				hayVacias = true;
			}
		}

		if (!hayVacias && ultimaIgual != -1) {
			dr = true;
		}
	}

	return iz || dr;
}

void JuegoOthello::convierteDiagonalDer(unsigned int c, unsigned int f) {
	
}

bool JuegoOthello::compruebaDiagonalDer(unsigned int c, unsigned int f) const {
	
	// Válida representa una ficha del color del jugador
	bool validaArDr, validaAbIz = false;

	// Vacía representa una casilla sin ficha
	bool vaciasArDr, vaciasAbIz = false;

	if ((enRango(c - 1, f - 1) && (dameCasilla(c - 1, f - 1) == cambia(turno))) || (enRango(c + 1, f + 1) && (dameCasilla(c + 1, f + 1) == cambia(turno)))) {

		unsigned int filaAr = f - 2;
		unsigned int colAr = c - 2;
		unsigned int filaAb = f + 2;
		unsigned int colAb = c - 2;

		while (!vaciasArDr && !validaArDr && enRango(colAr, filaAr)) {

			if (dameCasilla(colAr, filaAr) == Jn) {
				vaciasArDr = true;
			}
			else {
				if (dameCasilla(colAr, filaAr) == turno) {
					vaciasArDr = true;
				}
			}

			filaAr++;
			colAr++;
		}

		while (!vaciasAbIz && !validaAbIz && enRango(c, filaAb)) {

			if (dameCasilla(c, filaAb) == Jn) {
				vaciasAbIz = true;
			}
			else {
				if (dameCasilla(c, filaAb) == turno) {
					validaAbIz = true;
				}
			}

			filaAb++;
		}
	}

	return (validaArDr && !vaciasArDr) || (validaAbIz && !vaciasAbIz);
}

void JuegoOthello::convierteDiagonalIzq(unsigned int c, unsigned int f) {
	
}

bool JuegoOthello::compruebaDiagonalIzq(unsigned int c, unsigned int f) const {
	return true;
}
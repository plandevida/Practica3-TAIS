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

		if (c == 9) {
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

			//convierteHorizontal(c, f);
			//convierteVertical(c, f);
			//convierteDiagonalDer(c, f);
			//convierteDiagonalIzq(c, f);

			if (!ganador) turno = cambia(turno);
		}
	}
	else throw EJuego("Jugada incorrecta");
}

bool JuegoOthello::othello(unsigned int c, unsigned int f) {
	bool res = false;

	if ( fin() ) {

	}

	return res;
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

	for (unsigned int i = 0; i < c; i++) {

		if (dameCasilla(i, f) == turno) {
			ultimaIgual = i;
		}
		else if (ultimaIgual != -1 && dameCasilla(i, f) == Jn) {
			hayVacias = true;
		}
	}

	if (!hayVacias && ultimaIgual != -1) {
		iz =  true;
	}

	ultimaIgual = -1;
	hayVacias = false;

	for (unsigned int j = 8; j > c; j--) {

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

	return iz || dr;

	/*
	// Válida representa una ficha del color del jugador
	bool validaIz, validaDr = false;

	// Vacía representa una casilla sin ficha
	bool vaciasIz, vaciasDr = false;

	if ((enRango(c - 1, f) && (dameCasilla(c - 1, f) == cambia(turno))) || (enRango(c + 1, f) && (dameCasilla(c + 1, f) == cambia(turno)))) {

		unsigned int colIzq = c - 2;
		unsigned int colDrc = c + 2;

		while (!vaciasIz && !validaIz && enRango(colIzq, f)) {

			if (dameCasilla(colIzq, f) == Jn) {
				vaciasIz = true;
			}
			else {
				if (dameCasilla(colIzq, f) == turno) {
					validaIz = true;
				}
			}

			colIzq--;
		}

		while (!vaciasDr && !validaDr && enRango(colDrc, f)) {

			if (dameCasilla(colDrc, f) == Jn) {
				vaciasDr = true;
			}
			else {
				if (dameCasilla(colDrc, f) == turno) {
					validaDr = true;
				}
			}

			colDrc++;
		}
	}

	return (validaIz && !vaciasIz) || (validaDr && !vaciasDr);*/
}

void JuegoOthello::convierteDiagonalDer(unsigned int c, unsigned int f) {
	tablero->at(0, 2) == turno && tablero->at(1, 1) == turno && tablero->at(2, 0) == turno;
}

bool JuegoOthello::compruebaDiagonalDer(unsigned int c, unsigned int f) const {
	return true;
}

void JuegoOthello::convierteDiagonalIzq(unsigned int c, unsigned int f) {
	tablero->at(0, 0) == turno && tablero->at(1, 1) == turno && tablero->at(2, 2) == turno;
}

bool JuegoOthello::compruebaDiagonalIzq(unsigned int c, unsigned int f) const {
	return true;
}
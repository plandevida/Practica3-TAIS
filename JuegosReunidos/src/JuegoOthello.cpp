/*
* JuegoOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "JuegoOthello.h"

JuegoOthello::JuegoOthello(Turno JI) : libres( ((numCols)*numFils) - 4), hapasado(false) {

	numFichas[0] = 0;
	numFichas[1] = 0;
	cas = Casilla(3, 4);

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

		// Se ha pasado turno
		if (c == numCols) {
			if (!haPasado()) {
				setHaPasado(true);

				//ganador = othello(c, f);

				if (!ganador) turno = cambia(turno);
			}
			else {
				ganador = othello(c, f);
			}
		}
		else { // Se puede poner ficha

			setHaPasado(false);

			tablero->at(c, f) = turno;
			// Se guarda la última casilla donde se puso ficha
			cas = Casilla(c, f);
			libres--;

			// Aumenta el número de fichas del jugador
			if (turno == Jhum)
				numFichas[0]++;
			else if (turno == Jmaq)
				numFichas[1]++;

			// Convierte las fichas del contrario
			convierteHorizontal(c, f);
			convierteVertical(c, f);
			convierteDiagonalDer(c, f);
			convierteDiagonalIzq(c, f);

			// Determina si hay ganador
			ganador = othello(c, f);

			// Pone el turno del ganador, en 
			// función del número de fichas
			// para que aparezca en la ventana.
			if (ganador) {
				if (getBlancas() > getNegras()) {

					turno = Jhum;
				}
				else if (getBlancas() < getNegras()) {
					turno = Jmaq;
				}
				else {
					turno = Jn;
				}
			}

			// Si hay ganador no se cambia el turno
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

					// Comprobamos que el contrario tampoco puede poner
					turno = cambia(turno);

					if (!sePuede(col, fil)) {
						res = true;
					}
					else {
						res = false;

						// Se reestablece el turno anterior antes de salir
						// del bucle
						turno = cambia(turno);
						break;
					}

					// Se reestablece el turno anterior
					turno = cambia(turno);
				}
				else {
					res = false;
					break;
				}
			}
			if (!res) {
				break;
			}
		}
	}

	return res;
}

bool JuegoOthello::compruebaPasar() const {
	bool res = false;

	// Se comprueba que no se puede poner en ninguna casilla libre
	for (int col = 0; col < 8; col++) {
		for (int fil = 0; fil < 8; fil++) {

			if (!sePuede(col, fil)) {
				res = true;
			}
			else {
				res = false;
				break;
			}
		}
		if (!res) {
			break;
		}
	}
	
	return res;
}

void JuegoOthello::convierteVertical(unsigned int c, unsigned int f) {

	int fila = f - 2;
	bool infConvertida = false;
	bool supConvertida = false;

	int convertidas = 0;

	if (compruebaAbVertical(c, f)) {
		while (enRango(c, fila) && !infConvertida) {

			if (dameCasilla(c, fila) == turno) {

				// Desplazamos una casilla hacia arriba.
				fila++;

				while (fila <= f - 1) {

					tablero->at(c, fila) = turno;

					convertidas++;

					fila++;

					infConvertida = true;
				}
			}

			fila--;
		}
	}

	fila = f + 2;

	if (compruebaArVertical(c, f)) {
		while (enRango(c, fila) && !supConvertida) {

			if (dameCasilla(c, fila) == turno) {

				// Desplazamos una casilla hacia abajo.
				fila--;

				while (fila >= f + 1) {

					tablero->at(c, fila) = turno;

					convertidas++;

					fila--;

					supConvertida = true;
				}
			}

			fila++;
		}
	}

	if (turno == Jhum) {

		numFichas[0] += convertidas;
		numFichas[1] -= convertidas;
	}
	else if (turno == Jmaq) {

		numFichas[1] += convertidas;
		numFichas[0] -= convertidas;
	}
}

bool JuegoOthello::compruebaVertical(unsigned int c, unsigned int f) const {

	return compruebaArVertical(c, f) || compruebaAbVertical(c, f);
}

bool JuegoOthello::compruebaArVertical(unsigned int c, unsigned int f) const{

	// Válida representa una ficha del color del jugador
	bool validaAr = false;

	// Vacía representa una casilla sin ficha
	bool vaciasAr = false;

	if (enRango(c, f + 1) && (dameCasilla(c, f + 1) == cambia(turno))) {

		int filaAr = f + 2;

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
	}

	return validaAr && !vaciasAr;
}

bool JuegoOthello::compruebaAbVertical(unsigned int c, unsigned int f) const {

	// Válida representa una ficha del color del jugador
	bool validaAb = false;

	// Vacía representa una casilla sin ficha
	bool vaciasAb = false;

	if ((enRango(c, f - 1) && (dameCasilla(c, f - 1) == cambia(turno)))) {

		int filaAb = f - 2;

		while (!vaciasAb && !validaAb && enRango(c, filaAb)) {

			if (dameCasilla(c, filaAb) == Jn) {
				vaciasAb = true;
			}
			else {
				if (dameCasilla(c, filaAb) == turno) {
					validaAb = true;
				}
			}

			filaAb--;
		}
	}

	return validaAb && !vaciasAb;
}

void JuegoOthello::convierteHorizontal(unsigned int c, unsigned int f) {

	unsigned int col = c - 2;
	bool izConvertida = false;
	bool drConvertida = false;

	int convertidas = 0;

	if (compruebaIzHorizontal(c, f)) {
		while (enRango(col, f) && !izConvertida) {

			if (dameCasilla(col, f) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;

				while (col <= c - 1) {

					tablero->at(col, f) = turno;

					convertidas++;

					col++;

					izConvertida = true;
				}
			}

			col--;
		}
	}

	col = c + 2;

	if (compruebaDrHorizontal(c, f)) {
		while (enRango(col, f) && !drConvertida) {

			if (dameCasilla(col, f) == turno) {

				// Desplazamos una casilla a la izq.
				col--;

				while (col >= c + 1) {

					tablero->at(col, f) = turno;

					convertidas++;

					col--;

					drConvertida = true;
				}
			}

			col++;
		}
	}

	if (turno == Jhum) {

		numFichas[0] += convertidas;
		numFichas[1] -= convertidas;
	}
	else if (turno == Jmaq) {

		numFichas[1] += convertidas;
		numFichas[0] -= convertidas;
	}
}

bool JuegoOthello::compruebaHorizontal(unsigned int c, unsigned int f) const {

	return compruebaIzHorizontal(c, f) || compruebaDrHorizontal(c, f);
}

bool JuegoOthello::compruebaIzHorizontal(unsigned int c, unsigned int f) const {

	// Válida representa una ficha del color del jugador
	bool validaIz = false;

	// Vacía representa una casilla sin ficha
	bool vaciasIz = false;

	if ((enRango(c - 1, f) && (dameCasilla(c - 1, f) == cambia(turno)))) {

		int colIz = c - 2;

		while (!vaciasIz && !validaIz && enRango(colIz, f)) {

			if (dameCasilla(colIz, f) == Jn) {
				vaciasIz = true;
			}
			else {
				if (dameCasilla(colIz, f) == turno) {
					validaIz = true;
				}
			}

			colIz--;
		}
	}

	return validaIz && !vaciasIz;
}

bool JuegoOthello::compruebaDrHorizontal(unsigned int c, unsigned int f) const {

	// Válida representa una ficha del color del jugador
	bool validaDr = false;

	// Vacía representa una casilla sin ficha
	bool vaciasDr = false;

	if ((enRango(c + 1, f) && (dameCasilla(c + 1, f) == cambia(turno)))) {

		int colDr = c + 2;

		while (!vaciasDr && !validaDr && enRango(colDr, f)) {

			if (dameCasilla(colDr, f) == Jn) {
				vaciasDr = true;
			}
			else {
				if (dameCasilla(colDr, f) == turno) {
					validaDr = true;
				}
			}

			colDr++;
		}
	}
	
	return validaDr && !vaciasDr;
}

void JuegoOthello::convierteDiagonalDer(unsigned int c, unsigned int f) {

	int col = c - 2;
	int fil = f - 2;
	bool izConvertida = false;
	bool drConvertida = false;

	int convertidas = 0;

	if (compruebaAbDiagonalDer(c, f)) {
		while (enRango(col, fil) && !izConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;
				fil++;

				while (col <= c - 1) {

					tablero->at(col, fil) = turno;

					convertidas++;

					col++;
					fil++;

					izConvertida = true;
				}
			}

			col--;
			fil--;
		}
	}

	col = c + 2;
	fil = f + 2;

	if (compruebaArDiagonalDer(c, f)) {
		while (enRango(col, fil) && !drConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la izq.
				col--;
				fil--;

				while (col >= c + 1) {

					tablero->at(col, fil) = turno;

					convertidas++;

					col--;
					fil--;

					drConvertida = true;
				}
			}

			col++;
			fil++;
		}
	}

	if (turno == Jhum) {

		numFichas[0] += convertidas;
		numFichas[1] -= convertidas;
	}
	else if (turno == Jmaq) {

		numFichas[1] += convertidas;
		numFichas[0] -= convertidas;
	}
}

bool JuegoOthello::compruebaDiagonalDer(unsigned int c, unsigned int f) const {

	return compruebaArDiagonalDer(c, f) || compruebaAbDiagonalDer(c, f);
}

bool JuegoOthello::compruebaArDiagonalDer(unsigned int c, unsigned int f) const{

	// Válida representa una ficha del color del jugador
	bool validaArDr = false;

	// Vacía representa una casilla sin ficha
	bool vaciasArDr = false;

	if ((enRango(c + 1, f + 1) && (dameCasilla(c + 1, f + 1) == cambia(turno)))) {

		int filaAr = f + 2;
		int colAr = c + 2;

		while (!vaciasArDr && !validaArDr && enRango(colAr, filaAr)) {

			if (dameCasilla(colAr, filaAr) == Jn) {
				vaciasArDr = true;
			}
			else {
				if (dameCasilla(colAr, filaAr) == turno) {
					validaArDr = true;
				}
			}

			filaAr++;
			colAr++;
		}
	}
	
	return validaArDr && !vaciasArDr;
}

bool JuegoOthello::compruebaAbDiagonalDer(unsigned int c, unsigned int f) const{

	// Válida representa una ficha del color del jugador
	bool validaAbIz = false;

	// Vacía representa una casilla sin ficha
	bool vaciasAbIz = false;

	if ((enRango(c - 1, f - 1) && (dameCasilla(c - 1, f - 1) == cambia(turno)))) {

		int filaAb = f - 2;
		int colAb = c - 2;

		while (!vaciasAbIz && !validaAbIz && enRango(colAb, filaAb)) {

			if (dameCasilla(colAb, filaAb) == Jn) {
				vaciasAbIz = true;
			}
			else {
				if (dameCasilla(colAb, filaAb) == turno) {
					validaAbIz = true;
				}
			}

			filaAb--;
			colAb--;
		}
	}

	return validaAbIz && !vaciasAbIz;
}

void JuegoOthello::convierteDiagonalIzq(unsigned int c, unsigned int f) {

	int col = c - 2;
	int fil = f + 2;
	bool izConvertida = false;
	bool drConvertida = false;

	int convertidas = 0;

	if (compruebaArDiagonalIzq(c, f)) {
		while (enRango(col, fil) && !izConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;
				fil--;

				while (col <= c - 1) {

					tablero->at(col, fil) = turno;

					convertidas++;

					col++;
					fil--;

					izConvertida = true;
				}
			}

			col--;
			fil++;
		}
	}

	col = c + 2;
	fil = f - 2;

	if (compruebaAbDiagonalIzq(c, f)) {
		while (enRango(col, fil) && !drConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la izq.
				col--;
				fil++;

				while (col >= c + 1) {

					tablero->at(col, fil) = turno;

					convertidas++;

					col--;
					fil++;

					drConvertida = true;
				}
			}

			col++;
			fil--;
		}
	}

	if (turno == Jhum) {

		numFichas[0] += convertidas;
		numFichas[1] -= convertidas;
	}
	else if (turno == Jmaq) {

		numFichas[1] += convertidas;
		numFichas[0] -= convertidas;
	}
}

bool JuegoOthello::compruebaDiagonalIzq(unsigned int c, unsigned int f) const {

	return compruebaArDiagonalIzq(c, f) || compruebaAbDiagonalIzq(c, f);
}

bool JuegoOthello::compruebaArDiagonalIzq(unsigned int c, unsigned int f) const{

	// Válida representa una ficha del color del jugador
	bool validaArDr = false;

	// Vacía representa una casilla sin ficha
	bool vaciasArDr = false;

	if ((enRango(c - 1, f + 1) && (dameCasilla(c - 1, f + 1) == cambia(turno)))) {

		int filaAr = f + 2;
		int colAr = c - 2;

		while (!vaciasArDr && !validaArDr && enRango(colAr, filaAr)) {

			if (dameCasilla(colAr, filaAr) == Jn) {
				vaciasArDr = true;
			}
			else {
				if (dameCasilla(colAr, filaAr) == turno) {
					validaArDr = true;
				}
			}

			filaAr++;
			colAr--;
		}
	}

	return validaArDr && !vaciasArDr;
}

bool JuegoOthello::compruebaAbDiagonalIzq(unsigned int c, unsigned int f) const{

	// Válida representa una ficha del color del jugador
	bool validaAbIz = false;

	// Vacía representa una casilla sin ficha
	bool vaciasAbIz = false;

	if (enRango(c + 1, f - 1) && (dameCasilla(c + 1, f - 1) == cambia(turno))) {

		int filaAb = f - 2;
		int colAb = c + 2;

		while (!vaciasAbIz && !validaAbIz && enRango(colAb, filaAb)) {

			if (dameCasilla(colAb, filaAb) == Jn) {
				vaciasAbIz = true;
			}
			else {
				if (dameCasilla(colAb, filaAb) == turno) {
					validaAbIz = true;
				}
			}

			filaAb--;
			colAb++;
		}
	}

	return validaAbIz && !vaciasAbIz;
}
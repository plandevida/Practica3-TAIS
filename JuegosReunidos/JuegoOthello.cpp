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

	int fila = f - 2;
	bool infConvertida = false;
	bool supConvertida = false;

	if (compruebaAbVertical(c, f)) {
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
	}

	fila = f + 2;

	if (compruebaArVertical(c, f)) {
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
}

bool JuegoOthello::compruebaVertical(unsigned int c, unsigned int f) const {

	return compruebaArVertical(c, f) || compruebaAbVertical(c, f);
}

bool JuegoOthello::compruebaArVertical(unsigned int c, unsigned int f) const{

	// V�lida representa una ficha del color del jugador
	bool validaAr = false;

	// Vac�a representa una casilla sin ficha
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

	// V�lida representa una ficha del color del jugador
	bool validaAb = false;

	// Vac�a representa una casilla sin ficha
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

	if (compruebaIzHorizontal(c, f)) {
		while (enRango(col, f) && !izConvertida) {

			if (dameCasilla(col, f) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;

				while (col <= c - 1) {

					tablero->at(col, f) = turno;

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

					col--;

					drConvertida = true;
				}
			}

			col++;
		}
	}
}

bool JuegoOthello::compruebaHorizontal(unsigned int c, unsigned int f) const {

	return compruebaIzHorizontal(c, f) || compruebaDrHorizontal(c, f);
}

bool JuegoOthello::compruebaIzHorizontal(unsigned int c, unsigned int f) const {

	// V�lida representa una ficha del color del jugador
	bool validaIz = false;

	// Vac�a representa una casilla sin ficha
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

	// V�lida representa una ficha del color del jugador
	bool validaDr = false;

	// Vac�a representa una casilla sin ficha
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

	if (compruebaAbDiagonalDer(c, f)) {
		while (enRango(col, fil) && !izConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;
				fil++;

				while (col <= c - 1) {

					tablero->at(col, fil) = turno;

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

					col--;
					fil--;

					drConvertida = true;
				}
			}

			col++;
			fil++;
		}
	}
}

bool JuegoOthello::compruebaDiagonalDer(unsigned int c, unsigned int f) const {

	return compruebaArDiagonalDer(c, f) || compruebaAbDiagonalDer(c, f);
}

bool JuegoOthello::compruebaArDiagonalDer(unsigned int c, unsigned int f) const{

	// V�lida representa una ficha del color del jugador
	bool validaArDr = false;

	// Vac�a representa una casilla sin ficha
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

	// V�lida representa una ficha del color del jugador
	bool validaAbIz = false;

	// Vac�a representa una casilla sin ficha
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

	if (compruebaArDiagonalIzq(c, f)) {
		while (enRango(col, fil) && !izConvertida) {

			if (dameCasilla(col, fil) == turno) {

				// Desplazamos una casilla a la derecha.
				col++;
				fil--;

				while (col <= c - 1) {

					tablero->at(col, fil) = turno;

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

					col--;
					fil++;

					drConvertida = true;
				}
			}

			col++;
			fil--;
		}
	}
}

bool JuegoOthello::compruebaDiagonalIzq(unsigned int c, unsigned int f) const {

	return compruebaArDiagonalIzq(c, f) || compruebaAbDiagonalIzq(c, f);
}

bool JuegoOthello::compruebaArDiagonalIzq(unsigned int c, unsigned int f) const{

	// V�lida representa una ficha del color del jugador
	bool validaArDr, validaAbIz = false;

	// Vac�a representa una casilla sin ficha
	bool vaciasArDr, vaciasAbIz = false;

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

	// V�lida representa una ficha del color del jugador
	bool validaAbIz = false;

	// Vac�a representa una casilla sin ficha
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
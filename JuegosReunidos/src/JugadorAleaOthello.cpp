/*
* JugadorAleOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include <stdlib.h>
#include "JugadorAleaOthello.h"

#pragma unmanaged

Casilla JugadorAleaOthello::juega(const JuegoLogT2& EJ) const throw(EJugador) {

	if (typeid(EJ) != typeid(JuegoOthello)) throw EJugador();
	else {

		JuegoOthello* juegoOthello = (JuegoOthello*)&EJ;

		unsigned int columna = juegoOthello->getUltimaCasilla().col;
		unsigned int fila = juegoOthello->getUltimaCasilla().fil;

		// Marcamos la casilla usada por el jugador anterior
		casillasUsadas[columna][fila] = (juegoOthello->dameCasilla(columna, fila) != Jn);

		columnasFilas->clear();

		for (int c = 0; c < juegoOthello->numCols - 1; c++) {
			for (int f = 0; f < juegoOthello->numFils; f++)  {

				if (casillasUsadas[c][f] == false) {
					columnasFilas->push_back(Casilla(c, f));
				}
			}
		}

		if (EJ.final()) throw EJugador();
		int col, fil = -1;

		unsigned int cont = juegoOthello->getLibres();
		unsigned int numPares = columnasFilas->size();

		int index = rand() % numPares;

		list<Casilla>::iterator it = columnasFilas->begin();
		advance(it, index);

		Casilla cc = *it;

		col = cc.col;
		fil = cc.fil;

		if (!EJ.sePuede(col, fil))
			cont--;

		if (!casillasUsadas[col][fil]) {

			while (!EJ.sePuede(col, fil) && cont > 0) {

				numPares = columnasFilas->size();
				index = rand() % numPares;

				it = columnasFilas->begin();
				advance(it, index);

				cc = *it;

				col = cc.col;
				fil = cc.fil;

				if (!EJ.sePuede(col, fil))
					cont--;

				columnasFilas->erase(it);
			}
		}

		Casilla pone;

		if (cont == 0) {
			pone = Casilla(9, 1);
		}
		else {
			pone = Casilla(col, fil);
			casillasUsadas[col][fil] = true;
		}

		return pone;
	}
}

#pragma managed

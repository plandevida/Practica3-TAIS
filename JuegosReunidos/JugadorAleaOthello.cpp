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
		if (EJ.final()) throw EJugador();
		int col, fil;
		unsigned int Ncol = EJ.numCol();
		unsigned int Nfil = EJ.numFil();
		col = rand() % Ncol;
		fil = rand() % Nfil;
		while (!EJ.sePuede(col, fil)) {
			col = rand() % Ncol;
			fil = rand() % Nfil;
		}
		return Casilla(col, fil);
	}
}

#pragma managed

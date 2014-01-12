/*
* JugadorAleaOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef JUGADORALEAOTHELLO_H_
#define JUGADORALEAOTHELLO_H_

#include <list>
#include <iostream>
#include "JugadorAutoT2.h"
#include "JuegoOthello.h"

#pragma unmanaged

class JugadorAleaOthello : public JugadorAutoT2 {
private:
	list<Casilla> *columnasFilas;
	bool **casillasUsadas;

public:
	JugadorAleaOthello() {

		casillasUsadas = new bool*[8];
		columnasFilas = new list<Casilla>();

		for (int c = 0; c < 8; c++) {

			casillasUsadas[c] = new bool[8];

			for (int f = 0; f < 8; f++)  {

				casillasUsadas[c][f] = false;
			}
		}

		casillasUsadas[4][4] = true;
		casillasUsadas[3][3] = true;
		casillasUsadas[4][3] = true;
		casillasUsadas[3][4] = true;
	};

	virtual ~JugadorAleaOthello() {
		
		for (int i = 0; i < 8; i++) {
			delete[] casillasUsadas[i];
		}

		delete[] casillasUsadas;
		delete columnasFilas;
	}

	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugador);
};

#pragma managed
#endif // JUGADORALEOTHELLO_H_
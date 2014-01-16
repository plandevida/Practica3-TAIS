/*
* JugadorAleaOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include <list>
#include "JugadorMinimaxOthello.h"
#include "JugadorMinimaxT2.h"

#pragma unmanaged

float JugadorMinimaxOthello::heuristica(const JuegoLogT2* EJ, const Turno t) const {

	const int pesos[8][9] = {
		{ 50,  -1, 5, 2, 2, 5,  -1, 50 },
		{ -1, -10, 1, 1, 1, 1, -10, -1 },
		{  5,   1, 1, 1, 1, 1,   1,  5 },
		{  2,   1, 1, 0, 0, 1,   1,  2 },
		{  2,   1, 1, 0, 0, 1,   1,  2 },
		{  5,   1, 1, 1, 1, 1,   1,  5 },
		{ -1, -10, 1, 1, 1, 1, -10, -1 },
		{ 50,  -1, 5, 2, 2, 5,  -1, 50 }
	};

	float res = 0;
	int propias = 0;
	int contrarias = 0;

	for (int c = 0; c < EJ->numCol() -1; c++) {
		for (int f = 0; f < EJ->numFil(); f++) {

			if (EJ->dameCasilla(c, f) == t) {

				propias += pesos[f][c];
			}
			else if (EJ->dameCasilla(c, f) == cambia(t)) {

				contrarias += pesos[f][c];
			}
		}
	}

	return propias - contrarias;
}

#pragma managed

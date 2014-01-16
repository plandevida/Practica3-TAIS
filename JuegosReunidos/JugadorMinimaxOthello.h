/*
* JugadorAleaOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef JUGADORMINIMAXOTHELLO_H_
#define JUGADORMINIMAXOTHELLO_H_

#include <list>
#include <iostream>
#include "JugadorMinimaxT2.h"
#include "JuegoOthello.h"

#pragma unmanaged

class JugadorMinimaxOthello : public JugadorMinimaxT2 {
public:
	JugadorMinimaxOthello(unsigned int nivel) {

		JugadorMinimaxT2::setNivel(nivel);
	}

	~JugadorMinimaxOthello() {
	}

	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugadorMinimax) {

		Casilla c;

		if (typeid(EJ) != typeid(JuegoOthello)) throw new EJugadorMinimax();
		else {
			c = JugadorMinimaxT2::juega(EJ);
		}

		return c;
	}

	virtual float heuristica(const JuegoLogT2* EJ) const;
};

#pragma managed
#endif // JUGADORMINIMAXOTHELLO_H_

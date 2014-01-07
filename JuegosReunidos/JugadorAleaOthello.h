/*
* JugadorAleaOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef JUGADORALEAOTHELLO_H_
#define JUGADORALEAOTHELLO_H_

#include "JugadorAutoT2.h"
#include "JuegoOthello.h"

#pragma unmanaged

class JugadorAleaOthello : public JugadorAutoT2 {
public:
	JugadorAleaOthello() {};

	virtual ~JugadorAleaOthello() {};

	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugador);
};

#pragma managed
#endif // JUGADORALEOTHELLO_H_
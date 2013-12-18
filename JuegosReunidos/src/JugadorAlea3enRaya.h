/*
 * JugadorAlea3enRaya.h
 *
 *  Created on: 23/11/2012
 *      Author: alberto
 */

#ifndef JUGADORALEA3ENRAYA_H_
#define JUGADORALEA3ENRAYA_H_

#include "JugadorAutoT2.h"
#include "Juego3enRaya.h"

#pragma unmanaged


class JugadorAlea3enRaya : public JugadorAutoT2 {
public:
    JugadorAlea3enRaya(){
    };
    virtual ~JugadorAlea3enRaya(){
    };
    virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugador);

};

#pragma managed
#endif /* JUGADORALEA3ENRAYA_H_ */

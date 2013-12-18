/*
 * JugadorAutoT2.h
 *
 *  Created on: 22/11/2012
 *      Author: alberto
 */

#ifndef JUGADORAUTT2_H_
#define JUGADORAUTT2_H_

#include "JuegoLogT2.h"
#pragma unmanaged
//---------------------------------------------------------------------------

class EJugador { // error del jugador autom‡tico
private:
    string m;
public:
    EJugador(string m="Error del jugador automatico"):m(m){}
    string getMsg(){return m;}
};

class JugadorAutoT2 {
public:
    JugadorAutoT2(){};
    virtual ~JugadorAutoT2(){};

    // método abstracto que elige la posición del tablero donde jugar en el estado actual del juego EJ
    virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugador)=0;
};

#pragma managed
#endif /* JUGADORAUTT2_H_ */

/*
 * JugadorAlea3enRaya.cpp
 *
 *  Created on: 23/11/2012
 *      Author: alberto
 */

#include <stdlib.h>
#include "JugadorAlea3enRaya.h"
#pragma unmanaged

Casilla JugadorAlea3enRaya::juega(const JuegoLogT2& EJ) const throw(EJugador) {
    if (typeid(EJ) != typeid(Juego3enRaya)) throw EJugador();
    else {
        if (EJ.final()) throw EJugador();
        int col,fil;
        unsigned int Ncol=EJ.numCol();
        unsigned int Nfil=EJ.numFil();
        col=rand() % Ncol;
        fil=rand() % Nfil;
        while (!EJ.sePuede(col,fil)) {
            col=rand() % Ncol;
            fil=rand() % Nfil;
        }
        return Casilla(col,fil);
    }
}

#pragma managed
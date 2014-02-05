/*
 * JuegoLogT2.cpp
 *
 *  Created on: 22/11/2012
 *      Author: alberto
 */

#include "JuegoLogT2.h"
#pragma unmanaged

ostream& operator<<(ostream& o,const Casilla& ca){
    o << "Casilla: col = " << ca.col << ", fil = " << ca.fil << endl;
    return o;
}

// copia en el atributo el tablero del juego recibido como argumento
void JuegoLogT2::copiaTablero(const JuegoLogT2& EJ) {
    tablero=new Matriz<Ficha>(EJ.numCol(),EJ.numFil());
    for(unsigned int c=0; c<numCol(); c++)
        for(unsigned int f=0; f<numFil(); f++)
            tablero->at(c,f) = EJ.dameCasilla(c,f);
}

// deja el tablero vacío y el turno pasa a ser de JI
void JuegoLogT2::reinicia(Turno JI){
    turno = JI;
    ganador = false;
    for(unsigned int c=0; c<numCol(); c++)
        for(unsigned int f=0; f<numFil(); f++)
            tablero->at(c,f) = Jn;
}

#pragma managed

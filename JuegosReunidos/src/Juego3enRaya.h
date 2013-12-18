/*
 * Juego3enRaya.h
 *
 *  Created on: 23/11/2012
 *      Author: alberto
 */

#ifndef JUEGO3ENRAYA_H_
#define JUEGO3ENRAYA_H_

#include "JuegoLogT2.h"
#pragma unmanaged

class Juego3enRaya : public JuegoLogT2 {
public:
    static const int numCols = 3;
    static const int numFils = 3;
private:
    unsigned int libres;
    bool conecta3(unsigned int c,unsigned int f);
    bool horizontal(unsigned int c,unsigned int f);
    bool vertical(unsigned int c,unsigned int f);
    bool subeDer(unsigned int c,unsigned int f);
    bool subeIzq(unsigned int c,unsigned int f);
public:
    Juego3enRaya(Turno JI=Jn) : libres(numCols*numFils){
        turno=JI;
        tablero=new Matriz<Ficha>(numCols,numFils,Jn);
    }
    Juego3enRaya(const Juego3enRaya& EJ) : JuegoLogT2(EJ) {
        libres=EJ.libres;
    }
    virtual ~Juego3enRaya(){

    }
    virtual void reinicia(Turno JI){
        JuegoLogT2::reinicia(JI);libres=numCols*numFils;
    }
    virtual bool fin() const {
        return libres==0;
    }
    virtual JuegoLogT2* clona() const {
        return new Juego3enRaya(*this);
    }
    virtual void aplicaJugada(unsigned int c,unsigned int f) throw(EJuego);
    virtual bool sePuede(unsigned int c,unsigned int f) const throw() {
        try {
            return dameCasilla(c,f)==Jn;
        } catch(EJuego &) { return false; }
        return false;
    }
};

#pragma managed
#endif /* JUEGO3ENRAYA_H_ */

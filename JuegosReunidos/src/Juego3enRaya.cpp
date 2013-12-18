/*
 * Juego3enRaya.cpp
 *
 *  Created on: 23/11/2012
 *      Author: alberto
 */

#include "Juego3enRaya.h"

#pragma unmanaged
void Juego3enRaya::aplicaJugada(unsigned int c,unsigned int f) throw(EJuego) {
    if(sePuede(c,f) && !ganador) {
        tablero->at(c,f)=turno;
        libres--;
        ganador=conecta3(c,f);
        if(!ganador) turno=cambia(turno);
    } else throw EJuego("Jugada incorrecta");
}

bool Juego3enRaya::conecta3(unsigned int c,unsigned int f) {
    return (vertical(c,f) || horizontal(c,f) || subeDer(c,f)|| subeIzq(c,f));
}

bool Juego3enRaya::vertical(unsigned int c,unsigned int f) {
    return tablero->at(c,0)==turno && tablero->at(c,1)==turno && tablero->at(c,2)==turno;
}

bool Juego3enRaya::horizontal(unsigned int c,unsigned int f) {
    return tablero->at(0,f)==turno && tablero->at(1,f)==turno && tablero->at(2,f)==turno;
}

bool Juego3enRaya::subeDer(unsigned int c,unsigned int f) {
    return tablero->at(0,2)==turno && tablero->at(1,1)==turno && tablero->at(2,0)==turno;
}

bool Juego3enRaya::subeIzq(unsigned int c,unsigned int f) {
    return tablero->at(0,0)==turno && tablero->at(1,1)==turno && tablero->at(2,2)==turno;
}

#pragma managed
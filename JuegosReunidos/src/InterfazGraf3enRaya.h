/*
 * InterfazGraf3enRaya.h
 *
 *  Created on: 23/11/2012
 *      Author: alberto
 */

#ifndef INTERFAZGRAF3ENRAYA_H_
#define INTERFAZGRAF3ENRAYA_H_
using namespace System::Drawing;

#include "InterfazGrafT2.h"
#include "Juego3enRaya.h"
#pragma unmanaged

class InterfazGraf3enRaya : public InterfazGrafT2 {
private:
    int ladoCasilla;
    virtual void muestraEst(Graphics^ canvas, const Juego3enRaya& EJ) const throw();
public:
    InterfazGraf3enRaya(int w, int h);
    virtual ~InterfazGraf3enRaya();

    virtual unsigned int dameColumna(unsigned int X) const throw(EInterfaz) { return X/ladoCasilla - 1;};

    virtual unsigned int dameFila(unsigned int Y) const throw(EInterfaz) { return Y/ladoCasilla - 1;};

    virtual void muestraEstado(Graphics^ canvas, const JuegoLogT2& EJ) const throw(EInterfaz);
};

#pragma managed
#endif /* INTERFAZGRAF3ENRAYA_H_ */

/*
* InterfazGrafOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef INTERFAZGRAFOTHELLO_H_
#define INTERFAZGRAFOTHELLO_H_
using namespace System::Drawing;

#include <sstream>
#include "InterfazGrafT2.h"
#include "JuegoOthello.h"
#pragma unmanaged

class InterfazGrafOthello : public InterfazGrafT2 {
private:
	int ladoCasilla;
	virtual void muestraEst(Graphics^ canvas, const JuegoOthello& EJ) const throw();

public:
	InterfazGrafOthello(int w, int h);

	virtual ~InterfazGrafOthello();

	virtual unsigned int dameColumna(unsigned int X) const throw(EInterfaz) { return X / ladoCasilla - 1; };

	virtual unsigned int dameFila(unsigned int Y) const throw(EInterfaz) { return Y / ladoCasilla - 1; };

	virtual void muestraEstado(Graphics^ canvas, const JuegoLogT2& EJ) const throw(EInterfaz);
};

#pragma managed
#endif /* INTERFAZGRAFOTHELLO_H_ */
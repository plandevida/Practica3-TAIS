/*
 * InterfazGrafT2.h
 *
 *  Created on: 22/11/2012
 *      Author: alberto
 */

#ifndef INTERFAZGRAFT2_H_
#define INTERFAZGRAFT2_H_

#include <Windows.h>
#include "JuegoLogT2.h"
#include <string>
using namespace std;
using namespace System::Drawing;

#pragma unmanaged

class EInterfaz {
private:
    string m;
public:
    EInterfaz(string msg="Error de la interfaz gr‡fica"):m(msg){}
    ~EInterfaz(){}
    string getMsg()const throw(){return m;}
}; // errores de InterfazGraf

class InterfazGrafT2 {
protected:
	int window_width;   // anchura del lienzo donde se pinta el juego
	int window_height;  // altura del lienzo

public:
	InterfazGrafT2(int w, int h);
	virtual ~InterfazGrafT2();

    // devuelve la columna del tablero correspondiente a la coordenada X
    virtual unsigned int dameColumna(unsigned int X) const throw(EInterfaz)=0;

    // devuelve la fila del tablero correspondiente a la coordenada Y
    virtual unsigned int dameFila(unsigned int Y) const throw(EInterfaz)=0;

    // devuelve la casilla del tablero correspondiente a las coordenadas X e Y
    Casilla dameCasilla(unsigned int X, unsigned int Y) const throw(EInterfaz){
        return Casilla(dameColumna(X), dameFila(Y));
    }

    // dibuja sobre el lienzo el estado del juego EJ
	virtual void muestraEstado(Graphics^ canvas, const JuegoLogT2& EC)const throw(EInterfaz)=0;
};

string convertInt(int number);

#pragma managed

#endif /* INTERFAZGRAFT2_H_ */

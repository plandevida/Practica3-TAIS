/*
* InterfazGrafOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "InterfazGrafOthello.h"

using namespace System::Drawing;

InterfazGrafOthello::InterfazGrafOthello(int w, int h) : InterfazGrafT2(w, h), ladoCasilla(window_width/11) {}
InterfazGrafOthello::~InterfazGrafOthello() {}

void InterfazGrafOthello::muestraEst(Graphics^ canvas, const JuegoOthello& EJ) const throw() {

	canvas->FillRectangle(Brushes::Gainsboro, 0, 0, window_width, window_height); // borra el tablero

	// rotulo informativo
	Font^ letra = gcnew Font("Arial", 12);
	Point pr(150, 40);
	if (!EJ.final())
		switch (EJ.dameTurno()){
		case Jhum: canvas->DrawString("Turno usuario", letra, Brushes::Blue, pr); break;
		case Jmaq: canvas->DrawString("Turno máquina", letra, Brushes::Blue, pr); break;
	}
	else {
		switch (EJ.dameGanador()){
		case Jhum: canvas->DrawString("GANADOR: Usuario", letra, Brushes::Red, pr); break;
		case Jmaq: canvas->DrawString("GANADOR: Máquina", letra, Brushes::Red, pr); break;
		case Jn: canvas->DrawString("EMPATE", letra, Brushes::Red, pr); break;
		}
	}

	unsigned int c, f, x, y;
	for (c = 0; c<EJ.numCol(); c++) {
		x = (c + 1)*ladoCasilla;
		for (f = 0; f<EJ.numFil(); f++) {
			y = window_height - (f + 2)*ladoCasilla;  // dar la vuelta: y crece hacia abajo

			// dibuja el fondo de la casilla
			canvas->FillRectangle(Brushes::Chocolate, x, y, ladoCasilla - 2, ladoCasilla - 2);

			Ficha fi = EJ.dameCasilla(c, f);
			switch (fi){
			case Jn:  break;
			case Jhum: // ficha del humano: circulo blanco
				canvas->FillEllipse(Brushes::White, x + 10, y + 10, ladoCasilla - 20, ladoCasilla - 20);
				break;
			case Jmaq: // ficha de la maquina: circulo negro
				canvas->FillEllipse(Brushes::Black, x + 10, y + 10, ladoCasilla - 20, ladoCasilla - 20);
				break;
			}
		}
	}
}

void InterfazGrafOthello::muestraEstado(Graphics^ canvas, const JuegoLogT2& EJ) const throw(EInterfaz) {

	if (typeid(EJ) != typeid(JuegoOthello)) {
		throw EInterfaz();
	}
	else {
		muestraEst(canvas, (const JuegoOthello&) EJ);
	}
}

/*
* InterfazGrafOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#include "InterfazGrafOthello.h"

using namespace System::Drawing;

InterfazGrafOthello::InterfazGrafOthello(int w, int h) : InterfazGrafT2(w, h), ladoCasilla(window_width/10) {}
InterfazGrafOthello::~InterfazGrafOthello() {}

void InterfazGrafOthello::muestraEst(Graphics^ canvas, const JuegoOthello& EJ) const throw() {

	canvas->FillRectangle(Brushes::Gainsboro, 0, 0, window_width, window_height); // borra el tablero

	// rotulo informativo
	Font^ letra = gcnew Font("Arial", 12);
	Point pr(150, 20);
	if (!EJ.final())
		switch (EJ.dameTurno()){
		case Jhum: canvas->DrawString("Turno usuario", letra, Brushes::Blue, pr); break;
		case Jmaq: canvas->DrawString("Turno m�quina", letra, Brushes::Blue, pr); break;
	}
	else {

		switch (EJ.dameGanador()){
		case Jhum: canvas->DrawString("GANADOR: Usuario", letra, Brushes::DeepSkyBlue, pr); break;
		case Jmaq: canvas->DrawString("GANADOR: M�quina", letra, Brushes::Orange, pr); break;
		case Jn: canvas->DrawString("EMPATE", letra, Brushes::Red, pr); break;
		}
	}

	unsigned int c, f, x, y;
	for (c = 0; c<EJ.numCol(); c++) {
		x = (c + 1)*ladoCasilla;
		for (f = 0; f<EJ.numFil(); f++) {
			y = window_height - (f + 2)*ladoCasilla;  // dar la vuelta: y crece hacia abajo

			// dibuja el fondo de la casilla
			canvas->FillRectangle(Brushes::DarkViolet, x, y, ladoCasilla - 2, ladoCasilla - 2);

			Ficha fi = EJ.dameCasilla(c, f);
			switch (fi){
			case Jn:  break;
			case Jhum: // ficha del humano: circulo blanco
				canvas->FillEllipse(Brushes::DeepSkyBlue, x + 4, y + 4, ladoCasilla - 10, ladoCasilla - 10);
				break;
			case Jmaq: // ficha de la maquina: circulo negro
				canvas->FillEllipse(Brushes::Orange, x + 4, y + 4, ladoCasilla - 10, ladoCasilla - 10);
				break;
			}
		}
	}

	// Pintar la palabra PASAR en la columna 9
	int g = window_width - ladoCasilla + ladoCasilla/4;
	Point po(g, window_height - (EJ.numFil()+1)*ladoCasilla);
	canvas->DrawString("P\n\nA\n\nS\n\nA\n\nR\n\n\nT\n\nU\n\nR\n\nN\n\nO", letra, Brushes::Black, po);

	// Pintar el n�mero de fichas de cada color
	Point posfichas(100, window_height - 3*(ladoCasilla / 4 ));

	// Concatenaciones bizarras de C++
	std::ostringstream oss;
	oss << "Libres: " << EJ.getLibres() << ", Azules: " << EJ.getBlancas() << ", Naranjas: " << EJ.getNegras();
	System::String^ cadena = gcnew System::String(oss.str().c_str());

	canvas->DrawString(cadena, letra, Brushes::Black, posfichas);
}

void InterfazGrafOthello::muestraEstado(Graphics^ canvas, const JuegoLogT2& EJ) const throw(EInterfaz) {

	if (typeid(EJ) != typeid(JuegoOthello)) {
		throw EInterfaz();
	}
	else {
		muestraEst(canvas, (const JuegoOthello&) EJ);
	}
}

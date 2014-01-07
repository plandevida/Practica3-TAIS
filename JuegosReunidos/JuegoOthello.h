/*
* JuegoOthello.h
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef JUEGOOTHELLO_H_
#define JUEGOOTHELLO_H_

#include "JuegoLogT2.h"
#pragma unmanaged

class JuegoOthello : public JuegoLogT2 {

public:
	static const int numCols = 9;
	static const int numFils = 8;
private:
	unsigned int libres;

	// Guarda el número de fichas de cada color
	// puestas en el tablero
	// numFichas[0] -> Jhum
	// numFichas[1] -> Jmaq
	unsigned int numFichas[2];

	// Si el jugador anterior ha pasado de turno
	bool hapasado;

	bool othello(unsigned int c, unsigned int f);
	bool horizontal(unsigned int c, unsigned int f);
	bool vertical(unsigned int c, unsigned int f);
	bool subeDer(unsigned int c, unsigned int f);
	bool subeIzq(unsigned int c, unsigned int f);

	bool haPasado();
public:
	JuegoOthello(Turno JI = Jn);

	JuegoOthello(const JuegoOthello& EJ);

	virtual ~JuegoOthello() {}

	virtual void reinicia(Turno JI){
		JuegoLogT2::reinicia(JI);
		
		libres = numCols*numFils - 4;

		tablero->at(3, 3) = Jhum;
		tablero->at(4, 4) = Jhum;
		numFichas[0] += 2;

		tablero->at(4, 3) = Jmaq;
		tablero->at(3, 4) = Jmaq;
		numFichas[1] += 2;
	}

	virtual bool fin() const {
		return libres == 0;
	}

	virtual JuegoLogT2* clona() const {
		return new JuegoOthello(*this);
	}

	virtual void aplicaJugada(unsigned int c, unsigned int f) throw(EJuego);

	virtual bool sePuede(unsigned int c, unsigned int f) const throw() {
		try {
			return dameCasilla(c, f) == Jn;
		}
		catch (EJuego &) {
			return false;
		}

		return false;
	}

	unsigned int getBlancas() const {
		return numFichas[0];
	}

	unsigned int getNegras() const {
		return numFichas[1];
	}

	unsigned int getLibres() const {
		return libres;
	}
};

#pragma managed
#endif /* JUEGOOTHELLO_H_ */

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
	bool conecta3(unsigned int c, unsigned int f);
	bool horizontal(unsigned int c, unsigned int f);
	bool vertical(unsigned int c, unsigned int f);
	bool subeDer(unsigned int c, unsigned int f);
	bool subeIzq(unsigned int c, unsigned int f);
public:
	JuegoOthello(Turno JI = Jn);

	JuegoOthello(const JuegoOthello& EJ);

	virtual ~JuegoOthello() {}

	virtual void reinicia(Turno JI){
		JuegoLogT2::reinicia(JI); libres = numCols*numFils;
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
};

#pragma managed
#endif /* JUEGOOTHELLO_H_ */

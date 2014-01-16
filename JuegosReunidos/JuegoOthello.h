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

	// Cuantas casillas libres quedan
	unsigned int libres;

	// Guarda el número de fichas de cada color
	// puestas en el tablero
	// numFichas[0] -> Jhum
	// numFichas[1] -> Jmaq
	unsigned int numFichas[2];

	// Si el jugador anterior ha pasado de turno
	bool hapasado;

	// Casilla de la última ficha puesta
	Casilla cas;

	bool othello(unsigned int c, unsigned int f);

	void convierteHorizontal(unsigned int c, unsigned int f);
	bool compruebaHorizontal(unsigned int c, unsigned int f) const;
	bool compruebaIzHorizontal(unsigned int c, unsigned int f) const;
	bool compruebaDrHorizontal(unsigned int c, unsigned int f) const;

	void convierteVertical(unsigned int c, unsigned int f);
	bool compruebaVertical(unsigned int c, unsigned int f) const;
	bool compruebaArVertical(unsigned int c, unsigned int f) const;
	bool compruebaAbVertical(unsigned int c, unsigned int f) const;

	void convierteDiagonalDer(unsigned int c, unsigned int f);
	bool compruebaDiagonalDer(unsigned int c, unsigned int f) const;
	bool compruebaArDiagonalDer(unsigned int c, unsigned int f) const;
	bool compruebaAbDiagonalDer(unsigned int c, unsigned int f) const;

	void convierteDiagonalIzq(unsigned int c, unsigned int f);
	bool compruebaDiagonalIzq(unsigned int c, unsigned int f) const;
	bool compruebaArDiagonalIzq(unsigned int c, unsigned int f) const;
	bool compruebaAbDiagonalIzq(unsigned int c, unsigned int f) const;

	bool compruebaPasar() const;

	void setHaPasado(bool pasado) {
		hapasado = pasado;
	}
public:
	JuegoOthello(Turno JI = Jn);

	JuegoOthello(const JuegoOthello& EJ);

	virtual ~JuegoOthello() {}

	virtual void reinicia(Turno JI) {
		JuegoLogT2::reinicia(JI);
		
		libres = ((numCols - 1) * numFils) - 4;

		tablero->at(4, 4) = Jhum;
		tablero->at(3, 3) = Jhum;
		numFichas[0] += 2;

		tablero->at(3, 4) = Jmaq;
		tablero->at(4, 3) = Jmaq;
		numFichas[1] += 2;

		cas = Casilla(3, 4);
	}

	virtual bool fin() const {
		return libres == 0;
	}

	virtual JuegoLogT2* clona() const {
		return new JuegoOthello(*this);
	}

	virtual void aplicaJugada(unsigned int c, unsigned int f) throw(EJuego);

	virtual bool sePuede(unsigned int c, unsigned int f) const throw() {

		bool puede = false;

		try {
			if (c == 8) {
				if (compruebaPasar())
					puede = true;
			}
			else {
				puede = (dameCasilla(c, f) == Jn)
						&& (compruebaHorizontal(c, f)
							|| compruebaVertical(c, f)
							|| compruebaDiagonalDer(c, f)
							|| compruebaDiagonalIzq(c, f));
			}
		}
		catch (EJuego &) {
			return false;
		}

		return puede;
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

	bool haPasado() const {
		return hapasado;
	}

	Casilla getUltimaCasilla() const {
		return cas;
	}
};

#pragma managed
#endif /* JUEGOOTHELLO_H_ */

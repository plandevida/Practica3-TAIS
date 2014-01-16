/*
* JuegoOthello.cpp
*
*  Created on: 26/12/2013
*      Author: Daniel Serrano Torres
*/

#ifndef JUGADORMINIMAXT2_H_
#define JUGADORMINIMAXT2_H_

#include <algorithm>
#include "JuegoLogT2.h"
#include "JuegoOthello.h"
#include "JugadorAutoT2.h"

#pragma unmanaged

class EJugadorMinimax : public EJugador { // error del jugador inteligente
public:
	EJugadorMinimax(string ms = "Error del jugador inteligente") {
		EJugador::EJugador(ms);
	}
	string getMsg(){ return EJugador::getMsg(); }
};

class JugadorMinimaxT2 : public JugadorAutoT2 {
private:
	unsigned int nivel;
public:
	JugadorMinimaxT2() : nivel(3) {};
	virtual ~JugadorMinimaxT2() {};


	// m�todo abstracto que elige la posici�n del tablero donde jugar en el estado actual del juego EJ
	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugadorMinimax) {

		Casilla cas;

		bool pasarTurno = true;

		float mejorC;
		float mejorV = (-1)* std::numeric_limits<float>::infinity();

		for (int c = 0; c < EJ.numCol()-1; c++) {
			for (int f = 0; f < EJ.numFil(); f++) {

				JuegoLogT2* juego = EJ.clona();

				try {
					if (juego->sePuede(c, f)) {

						juego->aplicaJugada(c, f);

						pasarTurno = false;

						float infinito = std::numeric_limits<float>::infinity();

						float v = valoraMin(juego, nivel - 1, mejorV, infinito);

						if (v > mejorV) {
							mejorV = v;
							mejorC = c;
						}
					}
				}
				catch (EJuego e) {}

				if (juego != NULL) {
					delete juego;
				}
			}
		}

		if (pasarTurno) {
			cas = Casilla(8, 0);
		}
		else {
			cas.col = mejorC;
			cas.fil = mejorV;
		}

		return cas;
	}

	virtual float valoraMin(const JuegoLogT2* EJ, int n, float a, float b) const {

		float minimo;

		if (EJ->final() || n == 0) {
			minimo = heuristica(EJ);
		}
		else {
			for (int c = 0; c < EJ->numCol()-1; c++) {
				for (int f = 0; f < EJ->numFil(); f++) {

					JuegoLogT2* juego = EJ->clona();

					try {
						if (juego->sePuede(c, f)) {
							juego->aplicaJugada(c, f);

							b = min(valoraMax(juego, n - 1, a, b), b);

							if (a >= b) minimo = b;
						}
					}
					catch (EJuego e) {}

					if (juego != NULL) {
						delete juego;
					}
				}
			}
		}

		return minimo;
	}
	
	virtual float valoraMax(const JuegoLogT2* EJ, int n, float a, float b) const {

		float maximo;

		if (EJ->final() || n == 0) {
			maximo = heuristica(EJ);
		}
		else {

			for (int c = 0; c < EJ->numCol() - 1; c++) {
				for (int f = 0; f < EJ->numCol(); f++) {

					JuegoLogT2* juego = EJ->clona();

					try {
						if (juego->sePuede(c, f)) {
							juego->aplicaJugada(c, f);

							a = max(valoraMin(juego, n - 1, b, a), a);

							if (b >= a) maximo = a;
						}
					}
					catch (EJuego e) {}

					if (juego != NULL) {
						delete juego;
					}
				}
			}
		}

		return maximo;
	}

	virtual float heuristica(const JuegoLogT2* EJ) const = 0;

	void setNivel(unsigned int nivel) {
		this->nivel = nivel;
	}

	unsigned int getNivel() const {
		return nivel;
	}
};

#pragma managed
#endif /* JUGADORMINIMAXT2_H_ */
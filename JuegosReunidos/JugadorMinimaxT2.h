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
	JugadorMinimaxT2(unsigned int nivel = 4) : nivel(nivel) {};
	virtual ~JugadorMinimaxT2() {};


	// método abstracto que elige la posición del tablero donde jugar en el estado actual del juego EJ
	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugadorMinimax) {

		Casilla mejorCasilla;

		if (!EJ.final()) {

			Turno turno = EJ.dameTurno();

			float mejorV = -std::numeric_limits<float>::infinity();

			const float infinito = std::numeric_limits<float>::infinity();

			for (int c = 0; c < EJ.numCol(); c++) {
				for (int f = 0; f < EJ.numFil(); f++) {

					Casilla cas(c, f);

					if (EJ.sePuede(cas)) {

						JuegoLogT2* juego = EJ.clona();

						juego->aplicaJugada(c, f);

						float v = valoraMin(juego, turno, nivel - 1, mejorV, infinito);

						if (v > mejorV) {
							mejorV = v;
							mejorCasilla = cas;
						}

						delete juego;
						juego = NULL;
					}
				}
			}
		}
		else {
			throw new EJugadorMinimax();
		}

		return mejorCasilla;
	}

	virtual float valoraMin(const JuegoLogT2* EJ, Turno t, int n, float a, float b) const {

		float minimo;

		if (EJ->final() || n == 0) {
			minimo = heuristica(EJ, t);
		}
		else {
			for (int c = 0; c < EJ->numCol(); c++) {
				for (int f = 0; f < EJ->numFil(); f++) {

					if (EJ->sePuede(c, f)) {

						JuegoLogT2* juego = EJ->clona();

						juego->aplicaJugada(c, f);

						b = min(valoraMax(juego, t, n - 1, a, b), b);

						delete juego;
						juego = NULL;

						if (a >= b) minimo = b;
					}
				}
			}
		}

		return minimo;
	}

	virtual float valoraMax(const JuegoLogT2* EJ, Turno t, int n, float a, float b) const {

		float maximo;

		if (EJ->final() || n == 0) {
			maximo = heuristica(EJ, t);
		}
		else {

			for (int c = 0; c < EJ->numCol(); c++) {
				for (int f = 0; f < EJ->numCol(); f++) {

					if (EJ->sePuede(c, f)) {

						JuegoLogT2* juego = EJ->clona();

						juego->aplicaJugada(c, f);

						a = max(valoraMin(juego, t, n - 1, a, b), a);

						delete juego;
						juego = NULL;
						
						if (a >= b) maximo = a;
					}
				}
			}
		}

		return maximo;
	}

	virtual float heuristica(const JuegoLogT2* EJ, const Turno t) const = 0;

	void setNivel(unsigned int nivel) {
		this->nivel = nivel;
	}
};

#pragma managed
#endif /* JUGADORMINIMAXT2_H_ */
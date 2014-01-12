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


	// método abstracto que elige la posición del tablero donde jugar en el estado actual del juego EJ
	virtual Casilla juega(const JuegoLogT2& EJ) const throw(EJugadorMinimax) {

		Casilla mejorC;

		if (typeid(EJ) != typeid(JuegoOthello)) throw EJugadorMinimax();
		else {

			float mejorV = (-1)* std::numeric_limits<float>::infinity();

			for (int c = 0; c < 8; c++) {
				for (int f = 0; f < 8; f++) {

					JuegoLogT2* juego = EJ.clona();

					juego->aplicaJugada(c, f);
					float v = valoraMin(juego, nivel - 1);

					if (juego == NULL) {
						delete juego;
					}

					if (v > mejorV) {
						mejorV = v;
						mejorC = c;
					}
				}
			}
		}

		return mejorC;
	}

	virtual float valoraMin(JuegoLogT2* EJ, int n) const {

		float minimo;

		if (EJ->final() || n == 0) {
			minimo = heuristica(EJ);
		}
		else {
			float mejorV = std::numeric_limits<float>::infinity();

			for (int c = 0; c < 8; c++) {
				for (int f = 0; f < 8; f++) {

					JuegoLogT2* juego = EJ->clona();

					juego->aplicaJugada(c, f);

					mejorV = min(valoraMax(EJ, n - 1), mejorV);

					minimo = mejorV;

					if (juego == NULL) {
						delete juego;
					}
				}
			}
		}

		return minimo;
	}
	
	virtual float valoraMax(JuegoLogT2* EJ, int n) const {

		float maximo;

		if (EJ->final() || n == 0) {
			maximo = heuristica(EJ);
		}
		else {
			float mejorV = std::numeric_limits<float>::infinity();

			for (int c = 0; c < 8; c++) {
				for (int f = 0; f < 8; f++) {

					JuegoLogT2* juego = EJ->clona();

					juego->aplicaJugada(c, f);

					mejorV = max(valoraMin(EJ, n - 1), mejorV);

					maximo = mejorV;

					if (juego == NULL) {
						delete juego;
					}
				}
			}
		}

		return maximo;
	}

	virtual float heuristica(JuegoLogT2* EJ) const = 0;

	void setNivel(unsigned int nivel) {
		this->nivel = nivel;
	}

	unsigned int getNivel() const {
		return nivel;
	}
};

#pragma managed
#endif /* JUGADORMINIMAXT2_H_ */
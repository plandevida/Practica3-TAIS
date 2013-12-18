/*
 * JuegoLogT2.h
 *
 *  Created on: 22/11/2012
 *      Author: alberto
 */

#ifndef JUEGOLOGT2_H_
#define JUEGOLOGT2_H_

#include "Matriz.h"
#include <fstream>
#include <iostream>
using namespace std;

#pragma unmanaged

class EJuego { // error del juego
private:
    string m;
public:
    EJuego(const string& m="Error del juego"):m(m){}
    string getMsg(){return m;}
};

typedef enum {Jn,Jhum,Jmaq} Turno;
inline Turno cambia(Turno t){return (t==Jhum?Jmaq:Jhum);}

typedef Turno Ficha;

class Casilla {
public:
    unsigned int col;
    unsigned int fil;
    Casilla(unsigned int c=0, unsigned int f=0):col(c),fil(f){};
};

ostream& operator<<(ostream& o,const Casilla& ca);


class JuegoLogT2 {
protected:
    Turno turno;  // indica cuál es el turno actual (a quién le toca jugar)
    bool ganador; // indica si ya hay un ganador
    Matriz<Ficha>* tablero; // puntero a una matriz cuyos elementos pueden ser
                            // Jn (casilla vacía), Jhum (casilla ocupada por el humano)
                            // o Jmaq (casilla ocupada por el ordenador).

    // copia en el atributo el tablero del juego recibido como argumento
    virtual void copiaTablero(const JuegoLogT2& EJ);
public:
    JuegoLogT2() : turno(Jn), ganador(false), tablero(NULL) {
    }
    JuegoLogT2(const JuegoLogT2& EJ) : turno(EJ.turno), ganador(EJ.ganador), tablero(NULL) {
        copiaTablero(EJ);
    }
    virtual ~JuegoLogT2(){
        delete tablero; tablero=NULL;
    }

    unsigned int numCol() const throw(){
        return tablero->numCols();
    }
    unsigned int numFil() const throw(){
        return tablero->numFilas();
    }
    Turno dameTurno() const throw(){
        return turno;
    }
    bool enRango(unsigned int c,unsigned int f) const throw(){
        return c<numCol() && f<numFil();
    }
    bool enRango(Casilla cf) const throw(){
        return enRango(cf.col,cf.fil);
    }
    Ficha dameCasilla(unsigned int c,unsigned int f) const throw(EJuego){
        if(enRango(c,f)) return tablero->at(c,f);
        else throw EJuego("Casilla erronea");
    }
    Ficha dameCasilla(Casilla cf) const throw(EJuego){
        return dameCasilla(cf.col,cf.fil);
    }

    // deja el tablero en su configuración inicial y el turno pasa a ser de JI
    virtual void reinicia(Turno JI);

    // método abstracto que determina si se puede jugar en la posición (c,f)
    virtual bool sePuede(unsigned int c,unsigned int f) const throw()=0;

    // análogo al anterior para la jugada cf
    bool sePuede(Casilla cf) const throw(){
        return sePuede(cf.col,cf.fil);
    }

    // método abstracto que aplica la jugada caracterizada por la posición (c,f) del tablero.
    // Si dicha jugada no es legal se lanza una excepción
    virtual void aplicaJugada(unsigned int c,unsigned int f) throw(EJuego)=0;

    // análogo al anterior para la jugada cf
    void aplicaJugada(Casilla cf) throw(EJuego) {
        aplicaJugada(cf.col,cf.fil);
    }

    // indica si no se pueden realizar más jugadas
    virtual bool fin() const=0;

    // indica si se ha alcanzado el final del juego, bien porque no se pueda seguir jugando
    // o porque ya haya ganador
    bool final() const throw(){
        return ganador || fin();
    }

    // devuelve si hay ganador
    bool hayGanador() const throw(){
        return ganador;
    }

    // devuelve el ganador, que por defecto es el turno actual cuando hay un ganador
    virtual Turno dameGanador() const throw(){
        if(ganador) return turno;
        else return Jn;
    }

    // método abstracto que devuelve un puntero a una copia del juego actual
    virtual JuegoLogT2* clona() const=0;
};


#pragma managed
#endif /* JUEGOLOGT2_H_ */

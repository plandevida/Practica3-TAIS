#include "JuegoOthello.h"


JuegoOthello::JuegoOthello(Turno JI = Jn) : libres(numCols*numFils){
	turno = JI;
	tablero = new Matriz<Ficha>(numCols, numFils, Jn);
}

JuegoOthello::JuegoOthello(const JuegoOthello& EJ) : JuegoLogT2(EJ) {
	libres = EJ.libres;
}


#ifndef MatrizH
#define MatrizH

#include <string>
using namespace std;

#pragma unmanaged
class EMatriz {
private:
    string m;
public:
    EMatriz(const string& m="Error en matriz"):m(m){}
    string getMsg(){return m;}
};

template <class T>
class Matriz {
private:
    int nCols;
    int nFilas;
    T** matriz;
public:
    Matriz(int col=0, int fil=0);
    Matriz(int col, int fil, const T& VI); // posible valorIni damenda =
    ~Matriz();
    int numFilas()const{return nFilas;};
    int numCols() const{return nCols;};
    const T& at(int c,int f)const{
        if(enRango(c,f))return matriz[c][f];
        else throw EMatriz("Posicion invalida");
    };
    T& at(int c,int f){
        if(enRango(c,f))return matriz[c][f];
        else throw EMatriz("Posicion invalida");
    };
    bool enRango(int c,int f)const{return (c<nCols && f<nFilas && c>=0 && f>=0);}
};

//-----------------------------------------------------

template <class T>
Matriz<T>::Matriz(int col,int fil){
    if(col==0 || fil==0) {nCols=nFilas=0; matriz=NULL;}
    else{
        nCols=col;
        nFilas=fil;
        matriz= new T*[nCols];
        for (int c=0; c<nCols; c++){
            matriz[c]= new T[nFilas]; // demanda construct sin arg
        }
    }
}
//-----------------------------------------------------
template <class T>
Matriz<T>::Matriz(int col,int fil, const T& VI){
    if(col==0 || fil==0) {nCols=nFilas=0; matriz=NULL;}
    else{
        nCols=col;
        nFilas=fil;
        matriz= new T*[nCols];
        for (int c=0; c<nCols; c++){
            matriz[c]= new T[nFilas];
            for (int f=0; f<nFilas; f++)
                matriz[c][f]= VI;  // demanda =
        }
    }
}
//-----------------------------------------------------
template <class T>
Matriz<T>::~Matriz(){
    for (int c=0; c<nCols; c++)
        delete[] matriz[c];
    delete[] matriz;
}
//-----------------------------------------------------
#pragma managed
#endif

#ifndef ALGORITMOA_H_
#define ALGORITMOA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Matriz.h"
#include "Nodo.h"


using namespace std;

class Algoritmo_A{
public:

	Algoritmo_A(Matriz<char> tablero, Nodo origen, Nodo destino) : _tablero(tablero), _origen(origen), _destino(destino), _meta(false), _fallo(false) {
		_abierta.push_back(_origen);
		execute();
	}

	bool existeSolucion(){return _meta;}
	bool existeFallo() {return _fallo;}

	bool exportarFichero(const string nombreFichero){
		ofstream fichero;
		fichero.open(nombreFichero);

		if(fichero.is_open()){
			fichero << _tablero.numfils() << " " << _tablero.numcols() << endl;
			fichero << _destino.posX << " " << _destino.posY << endl;
			fichero << _origen.posX << " " << _destino.posY << endl;
			for(int i=0; i<_tablero.numfils(); i++){
				for(int j=0; j<_tablero.numcols(); j++){
					if(_tablero[i][j] == 'X'){
						fichero << i << " " << j << endl;
					}
				}
			}

		}
		else return false;

		fichero.close();
		return true;
	}

private:

	void execute(){
		if (_abierta.empty()) {
			_fallo = true;
			return;
		}
		
		else while (_abierta.size() > 0) {
			Nodo m = _abierta.back();
			_abierta.pop_back();
			_cerrada.push_back(m);

			if (m == _destino) {
				_meta = true;
				return;
			}
			else for (size_t dir = 0; dir < 8; dir++) {
				Nodo n = siguienteNodo(m, dir);
				n.padre = &m;
				bool mejor = false;
				if (_tablero[n.posX][n.posY] != 'X') {
					float distOrigenaN = f(n);
				}


			}

		}
		
	}

	Nodo siguienteNodo(const Nodo &m, int dir) {
		Nodo siguiente;
		switch (dir) {
		case 0: siguiente = Nodo(m.posX - 1, m.posY - 1); break;//arriba,izquierda
		case 1: siguiente = Nodo(m.posX - 1, m.posY); break;//arriba
		case 2: siguiente = Nodo(m.posX - 1, m.posY + 1); break;//arriba,derecha
		case 3: siguiente = Nodo(m.posX, m.posY + 1); break;//derecha
		case 4: siguiente = Nodo(m.posX + 1, m.posY + 1); break;//abajo,derecha
		case 5: siguiente = Nodo(m.posX + 1, m.posY); break;//abajo
		case 6: siguiente = Nodo(m.posX + 1, m.posY - 1); break;//abajo,izquierda
		case 7: siguiente = Nodo(m.posX, m.posY - 1); break;//izquierda
		default: siguiente = m; break;
		}


		return siguiente;
	}

	//float 

	float f(Nodo n) {
		return 1;
	}

	Matriz<char> _tablero;
	Nodo _origen;
	Nodo _destino;
	bool _meta;
	bool _fallo;
	list<Nodo> _abierta;
	list<Nodo> _cerrada;
	list<Nodo> _mejorCamino;

};

#endif ALGORITMOA_H_
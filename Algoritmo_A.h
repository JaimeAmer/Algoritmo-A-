#ifndef ALGORITMOA_H_
#define ALGORITMOA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
#include <ctime>
#include <queue>
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
	list<Nodo> mejorCamino(){return _mejorCamino;}
	double tiempoEjecucion(){return _tiempoEjecucion;}

	bool exportarFichero(const string nombreFichero){
		ofstream fichero;
		fichero.open(nombreFichero);

		if(fichero.is_open()){
			fichero << _tablero.numfils() << " " << _tablero.numcols() << endl;
			fichero << _destino.posX << " " << _destino.posY << endl;
			fichero << _origen.posX << " " << _destino.posY << endl;
			for(size_t i=0; i<_tablero.numfils(); i++){
				for(size_t j=0; j<_tablero.numcols(); j++){
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
		clock_t inicioEjecucion = clock();
		if (_abierta.empty()) {
			_fallo = true;
			return;
		}
		
		else while (_abierta.size() > 0) {
			Nodo m = _abierta.back();
			if (m == _destino) {
				_meta = true;
				for (Nodo *aux = &_destino; aux->padre != NULL; aux = aux->padre){
					_mejorCamino.push_back(*aux->padre);
				}
				return;
			}

			_abierta.pop_back();
			_cerrada.push_back(m);

			for (size_t dir = 0; dir < 8; dir++) {
				Nodo n = siguienteNodo(m, dir);
				bool mejor = false;
				if (_tablero.posCorrecta(n.posX, n.posY) && _tablero[n.posX][n.posY] != 'X') {
					float distOrigenaN = distancia(_origen, n) + distancia(n, m);
					list<Nodo>::iterator it = findElemFromList(_abierta, n);
					if (it != _abierta.end()){
						_abierta.push_back(n);
						_abierta.sort();
						mejor = true;
					}
					else if (distOrigenaN < distancia(_origen, m)){
						mejor = true;
					}

					if (mejor){
						n.padre = &m;
					}
				}
			}
		}
		_tiempoEjecucion = clock() - inicioEjecucion;
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

	float distancia(const Nodo &origen, const Nodo &destino){
		return (float) sqrt(pow(destino.posX - origen.posX, 2) + pow(destino.posY + origen.posY, 2));
	}

	list<Nodo>::iterator findElemFromList(list<Nodo> &lista, const Nodo &n){
		list<Nodo>::iterator it;
		for (it = lista.begin(); it != lista.end() && *it != n; it++);
		return it;
	}

	Matriz<char> _tablero;
	Nodo _origen;
	Nodo _destino;
	bool _meta;
	bool _fallo;
	list<Nodo> _abierta;
	list<Nodo> _cerrada;
	list<Nodo> _mejorCamino;
	clock_t _tiempoEjecucion;

	class Comparador{
	public:
		Comparador(Nodo origen, Nodo destino) : _src(origen), _dst(destino) {};
		bool operator()(Nodo a, Nodo b){
			float distOrigenaN = distancia(_src, a) + distancia(a, b);

			return true;
		}
	private:
		float distancia(const Nodo &origen, const Nodo &destino){
			return (float)sqrt(pow(destino.posX - origen.posX, 2) + pow(destino.posY + origen.posY, 2));
		}
		Nodo _src;
		Nodo _dst;
	};

};

#endif ALGORITMOA_H_
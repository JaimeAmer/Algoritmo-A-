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

	Algoritmo_A(Matriz<Nodo> tablero, Nodo origen, Nodo destino) : _tablero(tablero), _origen(&_tablero[origen]), _destino(&_tablero[destino]), _meta(false), _fallo(false) {
		_abierta.push_back(&_tablero[*_origen]);
		execute();
	}

	bool existeSolucion(){return _meta;}
	bool existeFallo() {return _fallo;}
	list<Nodo*> mejorCamino(){return _mejorCamino;}
	double tiempoEjecucion(){return _tiempoEjecucion;}

	bool exportarFichero(const string nombreFichero){
		ofstream fichero;
		fichero.open(nombreFichero);

		if(fichero.is_open()){
			fichero << _tablero.numfils() << " " << _tablero.numcols() << endl;
			fichero << _destino->posX << " " << _destino->posY << endl;
			fichero << _origen->posX << " " << _destino->posY << endl;
			for(size_t i=0; i<_tablero.numfils(); i++){
				for(size_t j=0; j<_tablero.numcols(); j++){
					if(_tablero[i][j].esObstaculo()){
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
		if (_tablero[*_destino].esObstaculo()) {
			_fallo = true;
			return;
		}
		
		while (_abierta.size() > 0) {
			Nodo* actual = _abierta.back();
			if (actual == _destino) {
				_meta = true;
				for (Nodo *aux = actual->padre; aux->padre != NULL; aux = aux->padre){
					_mejorCamino.push_front(aux);
				}
				return;
			}

			_abierta.pop_back();
			_cerrada.push_back(actual);

			for (size_t dir = 0; dir < 8; dir++) {
				Nodo calcularSiguiente = siguienteNodo(actual, dir);
				if(_tablero.posCorrecta(calcularSiguiente)){
					Nodo *siguiente = &_tablero[calcularSiguiente];
					bool mejor = false;
					if (findElemFromList(_cerrada, *siguiente) != _cerrada.end())
						continue;

					if (!siguiente->visitado && !_tablero[*siguiente].esObstaculo()) {
						siguiente->visitado = true;
						float distOrigenaN = distancia(*_origen, *actual) + distancia(*siguiente, *actual);
						list<Nodo*>::iterator it = findElemFromList(_abierta, *actual);
						if (it == _abierta.end()) {
							_abierta.push_back(siguiente);
							ordenarListaAbierta();
							mejor = true;
						}
						else if (distOrigenaN < distancia(*_origen, *siguiente)) {
							mejor = true;
						}

						if (mejor) {
							siguiente->padre = actual;
						}
					}
				}
			}
		}
		_tiempoEjecucion = clock() - inicioEjecucion;
	}

	Nodo siguienteNodo(Nodo *m, int dir) {
		Nodo siguiente;
		switch (dir) {
		case 0: siguiente = Nodo(m->posX - 1, m->posY - 1); break;//arriba,izquierda
		case 1: siguiente = Nodo(m->posX - 1, m->posY); break;//arriba
		case 2: siguiente = Nodo(m->posX - 1, m->posY + 1); break;//arriba,derecha
		case 3: siguiente = Nodo(m->posX, m->posY + 1); break;//derecha
		case 4: siguiente = Nodo(m->posX + 1, m->posY + 1); break;//abajo,derecha
		case 5: siguiente = Nodo(m->posX + 1, m->posY); break;//abajo
		case 6: siguiente = Nodo(m->posX + 1, m->posY - 1); break;//abajo,izquierda
		case 7: siguiente = Nodo(m->posX, m->posY - 1); break;//izquierda
		default: siguiente = Nodo(-1,-1); break;
		}
		return siguiente;
	}

	float distancia(const Nodo &origen, const Nodo &destino){
		return (float) sqrt(pow(destino.posX-origen.posX,2) + pow(destino.posY-origen.posY,2));
	}

	list<Nodo*>::iterator findElemFromList(list<Nodo*> &lista, const Nodo &n){
		list<Nodo*>::iterator it;
		bool encontrado = false;
		for (it = lista.begin(); it != lista.end() && !encontrado; it++) {
			if (**it == n)
				encontrado = true;
		}
		return it;
	}

	void ordenarListaAbierta() {
		list<Nodo*> ordenada;
		while (!_abierta.empty()) {
			Nodo* min = _abierta.back();
			list<Nodo*>::iterator it;
			for (it = _abierta.begin(); it != _abierta.end(); it++) {
				if (min->antes(**it, *_origen, *_destino)) {
					min = *it;
				}
			}
			ordenada.push_back(min);
			_abierta.remove(min);
		}
		_abierta = ordenada;
	}

	Matriz<Nodo> _tablero;
	Nodo* _origen;
	Nodo* _destino;
	bool _meta;
	bool _fallo;
	list<Nodo*> _abierta;
	list<Nodo*> _cerrada;
	list<Nodo*> _mejorCamino;
	clock_t _tiempoEjecucion;

};

#endif ALGORITMOA_H_
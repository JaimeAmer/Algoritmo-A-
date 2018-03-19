#ifndef NODO_H_
#define NODO_H_

class Nodo {
public:
	size_t posX, posY;
	Nodo* padre;
	char tipo;
	bool visitado;

	Nodo() : posX(0), posY(0), tipo('\0'), visitado(false), padre(NULL){}
	Nodo(size_t x, size_t y) : posX(x), posY(y), tipo('\0'), visitado(false), padre(NULL){}
	Nodo(size_t x, size_t y, char t) : posX(x), posY(y), tipo(t), visitado(false), padre(NULL) {}
	~Nodo(){}

	bool antes(const Nodo &otro, const Nodo &src, const Nodo &dst) {
		Nodo actual = *this;

		float distanciaADestino = distancia(actual, dst) + distancia(src, actual);
		float distanciaBDestino = distancia(otro, dst) + distancia(src, otro);

		if (distanciaADestino < distanciaBDestino)
			return true;
		else return false;

	}

	bool esObstaculo() {
		return tipo == 'X';
	}

	friend std::ostream &operator<<(std::ostream &out, Nodo n) {
		if (n.tipo == 'A' || n.tipo == 'B')
			out << termcolor::green << n.tipo << termcolor::reset;
		else if (n.tipo == 'X')
			out << termcolor::magenta << n.tipo << termcolor::reset;
		else if (n.tipo == 's')
			out << termcolor::cyan << n.tipo << termcolor::reset;
		else out << n.tipo;

		return out;
	}

	bool operator==(const Nodo b) {
		return posX == b.posX && posY == b.posY;
	}

	bool operator!=(const Nodo b) {
		return !(*this == b);
	}

private:
	
	float distancia(const Nodo &origen, const Nodo &destino) {
		return (float)sqrt(pow(destino.posX - origen.posX, 2) + pow(destino.posY - origen.posY, 2));
	}

};

#endif NODO_H_
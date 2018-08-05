#ifndef PONTO_H
#define PONTO_H

class Ponto{

private:
	double x;
	double y;
	double z;

public:
	Ponto(double x, double y, double z);

	Ponto(double x, double y);

	double GetX();

	double GetY();

	double GetZ();
}

#endif //PONTO_H
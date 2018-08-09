#ifndef PONTO_H
#define PONTO_H

class Ponto{

private:
	double coord[3];

public:
	Ponto(double x, double y, double z);

	Ponto(double x, double y);

	double getX();

	double getY();

	double getZ();

	void calculateNewPos();
};

#endif //PONTO_H
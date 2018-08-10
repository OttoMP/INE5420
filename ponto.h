#ifndef PONTO_H
#define PONTO_H

class Ponto{

private:
	double coord[3];

public:
	Ponto(double x, double y, double z);

	Ponto(double x, double y);

	double get_x();

	double get_y();

	double get_z();

	void calc_new_pos();
};

#endif //PONTO_H
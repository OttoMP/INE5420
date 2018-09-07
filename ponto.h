#ifndef PONTO_H
#define PONTO_H

#include <cmath>
#include <limits>

class Ponto{

private:
	double coord[3];

public:
	Ponto(double x, double y, double z);

	Ponto(double x, double y);

	double get_x() const;

	double get_y() const;

	double get_z() const;

	void calc_new_pos();

    bool operator==(const Ponto& a);

    bool operator!=(const Ponto& a);
};

#endif //PONTO_H

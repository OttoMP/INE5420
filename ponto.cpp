#include "ponto.h"


Ponto::Ponto(double x, double y, double z)
{
	this->coord[0] = x;
	this->coord[1] = y;
	this->coord[2] = z;
}

Ponto::Ponto(double x, double y)
{
	this->coord[0] = x;
	this->coord[1] = y;
	this->coord[2] = 1;
}

double Ponto::get_x() const
{
	return this->coord[0];
}

double Ponto::get_y() const
{
	return this->coord[1];
}

double Ponto::get_z() const
{
	return this->coord[2];
}

bool Ponto::operator==(const Ponto& a) {
    return (this->coord[0] == a.get_x()) &&
           (this->coord[1] == a.get_y()) &&
           (this->coord[2] == a.get_z());
}

bool Ponto::operator!=(const Ponto& a) {
    return (this->coord[0] != a.get_x()) ||
           (this->coord[1] != a.get_y()) ||
           (this->coord[2] != a.get_z());
}

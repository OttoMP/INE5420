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

double Ponto::getX()
{
	return this->coord[0];
}

double Ponto::getY()
{
	return this->coord[1];
} 

double Ponto::getZ()
{
	return this->coord[2];
}

void Ponto::calculateNewPos()
{
	
}

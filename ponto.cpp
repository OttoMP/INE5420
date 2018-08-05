#include "ponto.h"


Ponto::Ponto(double x, double y, double z)
{
	this.x = x;
	this.y = y;
	this.z = z;
}

Ponto::Ponto(double x, double y)
{
	this.x = x;
	this.y = y;
	this.z = 0;
}

Ponto::GetX()
{
	return x;
}

Ponto::GetY()
{
	return y;
} 

Ponto::GetZ()
{
	return z;
}
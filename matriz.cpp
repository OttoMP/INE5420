#include "matriz.h"

Matriz::Matriz()
{
	
}

Matriz Matriz::translate(Ponto vector)
{
	this->matriz[2][0] = vector.get_x();
	this->matriz[2][1] = vector.get_y();
	this->matriz[2][2] = 0;
	return *this;
}

Matriz Matriz::rotate(double angle, Ponto rotation_center)
{
	this->matriz[0][0] = cos(angle*PI/180);
	this->matriz[1][1] = cos(angle*PI/180);
	this->matriz[1][0] = sin(angle*PI/180);
	this->matriz[0][1] = -sin(angle*PI/180);
	return this->multiplication(Matriz().translate(rotation_center));
	
}

Matriz Matriz::scale(Ponto scale, Ponto center)
{
	Matriz m = Matriz().translate(Ponto(0,0));
	this->matriz[0][0] = scale.get_x();
	this->matriz[1][1] = scale.get_y();
	this->matriz[2][2] = 0;
	m.multiplication(*this);
	m.multiplication(Matriz().translate(center));
	return m;
}

Matriz Matriz::multiplication(Matriz m)
{
	Matriz result = Matriz();

	for (int i = 0; i < DIMENSOES; i++)
	{
		for (int j = 0; j < DIMENSOES; j++)
		{
			int soma = 0;
			for (int x = 0; x < DIMENSOES; x++){
				soma += this->matriz[i][x] * m.matriz[x][j];
			}
			result.matriz[i][j] = soma;
		}
	}

	return result;
}

Ponto Matriz::exec_transform(Ponto p)
{
	double temp[3] = {};
	temp[0] = p.get_x();
	temp[1] = p.get_y();
	temp[2] = p.get_z();
	double result[3] = {};
	
	for (int j = 0; j < 3; j++)
	{
		int soma = 0;
		for (int x = 0; x < 3; x++)
		{
			soma += temp[x] * this->matriz[x][j];
		}
		result[j] = soma;
	}
	return Ponto(result[0], result[1], result[2]);
}


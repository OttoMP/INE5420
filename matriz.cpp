#include "matriz.h"

Matriz::Matriz()
{
	
}

Matriz Matriz::translate(Ponto vector)
{
	this->matriz[0][0] = 1;
	this->matriz[1][1] = 1;
	this->matriz[2][2] = 1;
	this->matriz[3][3] = 1;
	this->matriz[3][0] = vector.get_x();
	this->matriz[3][1] = vector.get_y();
	this->matriz[3][2] = vector.get_z();
	
	return *this;
}

Matriz Matriz::rotate(double angle, Ponto center, Ponto eixo)
{
	Matriz r1 = Matriz().get_rotation_matriz(calc_angulo(eixo, Ponto(1, 0, 0)), 0)
	Matriz r2 = Matriz().get_rotation_matriz(calc_angulo(eixo, Ponto(0, 0, 1)), 2)
	Matriz r3 = Matriz().get_rotation_matriz(angle, 1)
	Matriz r1n = Matriz().get_rotation_matriz(-calc_angulo(eixo, Ponto(1, 0, 0)), 0)
	Matriz r2n = Matriz().get_rotation_matriz(-calc_angulo(eixo, Ponto(0, 0, 1)), 2)
    Matriz m = Matriz().translate(Ponto(-center.get_x(),-center.get_y(), -center.get_z()))
	   .multiplication(*this)
	   .multiplication(r1)
	   .multiplication(r2)
	   .multiplication(r3)
	   .multiplication(r2n)
	   .multiplication(r1n)
	   .multiplication(Matriz().translate(Ponto(center.get_x(),center.get_y(), center.get_z())));
	return m;	
}

Matriz Matriz::scale(Ponto scale, Ponto center)
{
	this->matriz[0][0] = scale.get_x();
	this->matriz[1][1] = scale.get_y();
	this->matriz[2][2] = scale.get_z();
	this->matriz[3][3] = 1;
    Matriz m = Matriz().translate(Ponto(-center.get_x(),-center.get_y(), -center.get_z()))
	    .multiplication(*this)
	    .multiplication(Matriz().translate(Ponto(center.get_x(),center.get_y(), center.get_z())));
	    
	return m;
}	 	  	 	    	 	    		    	    	  	 	

Matriz Matriz::multiplication(Matriz m)
{
	Matriz result = Matriz();
    double soma = 0;
	for (int i = 0; i < DIMENSOES; i++)
	{
		for (int j = 0; j < DIMENSOES; j++)
		{
			soma = 0;
			for (int x = 0; x < DIMENSOES; x++){
				soma += this->matriz[i][x] * m.matriz[x][j];
			}
			result.matriz[i][j] = soma;
		}
	}

	return result;
}

Matriz Matriz::multiplication(double c)
{
    Matriz result = Matriz();
	for (int i = 0; i < DIMENSOES; i++)
	{
		for (int j = 0; j < DIMENSOES; j++)
		{
			result.matriz[i][j] = this->matriz[i][j] * c;
		}
	}

	return result;
}

Ponto Matriz::exec_transform(Ponto p)
{
	double temp[DIMENSOES] = {};
	temp[0] = p.get_x();
	temp[1] = p.get_y();
	temp[2] = p.get_z();
	temp[3] = 1;
	double result[DIMENSOES] = {};
	
	for (int j = 0; j < DIMENSOES; j++)
	{
		double soma = 0;
		for (int x = 0; x < DIMENSOES; x++)
		{
			soma += temp[x] * this->matriz[x][j];
		}
		result[j] = soma;
	}	 	  	 	    	 	    		    	    	  	 	
	return Ponto(result[0], result[1], result[2]);
}

void Matriz::set_matriz(double matriz[DIMENSOES][DIMENSOES])
{
    for (int i = 0; i<DIMENSOES; i++)
    {
        for (int j=0; j<DIMENSOES; j++)
        {
            this->matriz[i][j] = matriz[i][j];
        }
    }
}

void Matriz::set_matriz_delta(double delta)
{
    this->matriz[0][0] = 0;
    this->matriz[0][1] = 0;
    this->matriz[0][2] = 0;
    this->matriz[0][3] = 1;
    
    this->matriz[1][0] = delta * delta * delta;
    this->matriz[1][1] = delta * delta;
    this->matriz[1][2] = delta;
    this->matriz[1][3] = 0;
    
    this->matriz[2][0] = 6 * delta * delta * delta;
    this->matriz[2][1] = 2 * delta * delta;
    this->matriz[2][2] = 0;
    this->matriz[2][3] = 0;
    
    this->matriz[3][0] = 6 * delta * delta * delta;
    this->matriz[3][1] = 0;
    this->matriz[3][2] = 0;
    this->matriz[3][3] = 0;
}

double Matriz::get_pos(int x, int y)
{
    return this->matriz[x][y];
}

void Matriz::get_matriz(double matriz[DIMENSOES][DIMENSOES])
{
    for (int i = 0; i<DIMENSOES; i++)
    {
        for (int j=0; j<DIMENSOES; j++)
        {
            matriz[i][j] = this->matriz[i][j];
        }
    }
}

void Matriz::transpose()
{
    double result[DIMENSOES][DIMENSOES] = {};
        
    for (int i = 0; i<DIMENSOES; i++)
    {
        for (int j=0; j<DIMENSOES; j++)
        {
            result[i][j] = this->matriz[j][i];
        }
    }
    
    for (int i = 0; i<DIMENSOES; i++)
    {
        for (int j=0; j<DIMENSOES; j++)
        {
            this->matriz[i][j] = result[i][j];
        }
    }
}

Matriz Matriz::get_rotation_matrix(double angle, int eixo)
{
    if (eixo == 0)
    {
    	this->matriz[0][0] = 1;
    	this->matriz[1][1] = cos(angle*M_PI/180);
    	this->matriz[2][2] = cos(angle*M_PI/180);
    	this->matriz[2][1] = sin(angle*M_PI/180);
    	this->matriz[1][2] = -sin(angle*M_PI/180);
    	this->matriz[3][3] = 1;
    } else if (eixo == 1)
    {
        this->matriz[0][0] = cos(angle*M_PI/180);
    	this->matriz[2][2] = cos(angle*M_PI/180);
    	this->matriz[2][0] = sin(angle*M_PI/180);
    	this->matriz[0][2] = -sin(angle*M_PI/180);
    	this->matriz[1][1] = 1;
    	this->matriz[3][3] = 1;
        
    }else{
        this->matriz[0][0] = cos(angle*M_PI/180);
    	this->matriz[1][1] = cos(angle*M_PI/180);
    	this->matriz[1][0] = sin(angle*M_PI/180);
    	this->matriz[0][1] = -sin(angle*M_PI/180);
    	this->matriz[2][2] = 1;
    	this->matriz[3][3] = 1;
    }

	return *this;
}

double Matriz::calc_angulo(Ponto a, Ponto b) //só funciona quando b é vertical arrumar depois
{

    double cima = a.get_x()*b.get_x() + a.get_y()*b.get_y();
    double baixo = sqrt(pow(a.get_x(),2) + pow(a.get_y(),2))*
        sqrt(pow(b.get_x(),2)+pow(b.get_y(),2));
    double temp = cima/baixo;
    if (a.get_x() >=0 && a.get_y() <0 || a.get_x()>0 && a.get_y()>0){
        return -abs(acos(temp)*180/M_PI);
    } else {
        return abs(acos(temp)*180/M_PI);
    }

}


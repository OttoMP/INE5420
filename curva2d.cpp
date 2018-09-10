#include "curva2d.h"

Curva2D::Curva2D(int id, string nome)
{
    this->id = id;
    this->nome = nome;
}

int Curva2D::add_curva(Ponto p1, Ponto p2, Ponto p3, Ponto p4)
{
    if (this->get_size() == 0)
    {
        this->pontos.push_back(p1);
        this->pontos.push_back(p2);
        this->pontos.push_back(p3);
        this->pontos.push_back(p4);
        this->center = Ponto((p1.get_x()+p2.get_x() + p3.get_x() + p4.get_x())/4,
            (p1.get_y()+p2.get_y() + p3.get_y() + p4.get_y())/4);
    }
    else 
    {
        if (this->pontos.back() == p1){
            this->pontos.push_back(p1);
            this->pontos.push_back(p2);
            this->pontos.push_back(p3);
            this->pontos.push_back(p4);
            this->center = Ponto((p1.get_x()+p2.get_x() + p3.get_x() + p4.get_x() + this->center.get_x()*this->get_size())/(this->get_size()+4),
                (p1.get_y()+p2.get_y() + p3.get_y() + p4.get_y() + this->center.get_y()*this->get_size())/(this->get_size()+4));
        }
        else 
        {
            return -1;
        }
    }
    this->pontos.push_back(Ponto(0,0));
    this->pontos.push_back(Ponto(0,0));
    this->pontos.push_back(Ponto(0,0));
    this->pontos.push_back(Ponto(0,0));
    return 0;
}

std::list<Ponto> Curva2D::draw(double scale, double wmin_x, double wmax_x, double wmin_y, double wmax_y)
{
    std::list<Ponto> desenho;
    auto pt = this->pontos_scn.begin();
    if (this->get_size() % 4 == 0)
    {
        for (int i = 0; i < this->get_num_curvas(); i++)
        {
            Ponto p1 = *pt;
            pt++;
            Ponto p2 = *pt;
            pt++;
            Ponto p3 = *pt;
            pt++;
            Ponto p4 = *pt;
            pt++;
            int precision = PRECISON * (int)scale; 
            for (int t = 0; t < precison; t++)
            {
                double t2 = pow(t,2);
                double t3 = pow(t,3);
                double x = (-1*t3 + 3*t2 - 3*t + 1) * p1.get_x()
                    + (3*t3 - 6*t2 + 3*t) * p2.get_x() 
                    + (-3*t3 + 3*t2) * p3.get_x() 
                    + (t3) * p4.get_x();
                double y = (-1*t3 + 3*t2 - 3*t + 1) * p1.get_x()
                    + (3*t3 - 6*t2 + 3*t) * p2.get_x() 
                    + (-3*t3 + 3*t2) * p3.get_x() 
                    + (t3) * p4.get_x();

                if (x < wmin_x || x > wmax_x || y < wmin_y || y > wmax_y)
                {
                    //ponto fora da tela
                }
                else
                {
                    Ponto add = Ponto(x,y);
                    desenho.push_back(add);
                }
            }
        }
    }
    else
    {
        //nao tem pelo menos 4 pontos
    }
    return desenho;
}

int get_num_curvas() 
{
    return (int)(this->get_size()/4);
}
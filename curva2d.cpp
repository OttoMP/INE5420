#include "curva2d.h"

Curva2D::Curva2D(int id, string nome)
{
    this->id = id;
    this->nome = nome;
    this->tipo = 2;
}

Curva2D::Curva2D(string nome, std::list<Ponto> pontos)
{
    this->nome = nome;
    this->tipo = 2;
    this->set_pontos(pontos);
}

Curva2D::Curva2D(Objeto o)
{
    this->id = o.get_id();
    this->nome = o.get_nome();
    this->pontos = o.get_pontos();
    this->center = o.get_center();
    this->brush_size = o.get_brush_size();
    this->pontos_scn = o.get_pontos_scn();
    this->tipo = o.get_tipo();
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
    this->pontos_scn.push_back(Ponto(0,0));
    this->pontos_scn.push_back(Ponto(0,0));
    this->pontos_scn.push_back(Ponto(0,0));
    this->pontos_scn.push_back(Ponto(0,0));
    return 0;
}

void Curva2D::set_pontos(std::list<Ponto> pontos)
{
    if (pontos.size() % 4 == 0)
    {
        auto pt = pontos.begin();
        for (int i = 0; i < (int)(pontos.size()/4); i++)
        {
            Ponto p1 = *pt;
            pt++;
            Ponto p2 = *pt;
            pt++;
            Ponto p3 = *pt;
            pt++;
            Ponto p4 = *pt;
            pt++;
            this->add_curva(p1,p2,p3,p4);
        }	 	  	 	    	 	    		    	    	  	 	
    }
}

std::list<Ponto> Curva2D::draw(double scale)
{
    std::list<Ponto> desenho;
    auto pt = this->pontos_scn.begin();
    if (this->get_size() % 4 == 0)
    {
        for (int i = 0; i < this->get_num_curvas(); i++)
        {
            Ponto p1 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            pt++;
            Ponto p2 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            pt++;
            Ponto p3 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            pt++;
            Ponto p4 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            pt++;
            int precisao = 10*scale;
            double t = 0;
            double t2 = 0;
            double t3 = 0;
            double x = 0;
            double y = 0;
            double z = 0;
            bool clipping = true;
            for (int s = 0; s <= precisao; s++)
            {

                t = ((double)s) /((double)precisao);
                t2 = pow(t,2);
                t3 = pow(t,3);
                x = 0;
                y = 0;
                z = 0;
                double x = (-1*t3 + 3*t2 - 3*t + 1) * p1.get_x()
                    + (3*t3 - 6*t2 + 3*t) * p2.get_x()
                    + (-3*t3 + 3*t2) * p3.get_x()
                    + (t3) * p4.get_x();
                double y = (-1*t3 + 3*t2 - 3*t + 1) * p1.get_y()
                    + (3*t3 - 6*t2 + 3*t) * p2.get_y()
                    + (-3*t3 + 3*t2) * p3.get_y()
                    + (t3) * p4.get_y();
                double z = (-1*t3 + 3*t2 - 3*t + 1) * p1.get_z()
                    + (3*t3 - 6*t2 + 3*t) * p2.get_z()
                    + (-3*t3 + 3*t2) * p3.get_z()
                    + (t3) * p4.get_z();
                    /*
                x += ((((-1)*t3) + (3*t2) - (3*t) + 1) * 0.1);
                x += (((3*t3) - (6*t2) + (3*t)) * 0.1);
                x += ((((-3)*t3) + (3*t2)) * 0.3);
                x += ((t3) * 0.4);
                double y = (((((-1)*t3) + (3*t2) - (3*t) + 1) * 0.3)
                    + (((3*t3) - (6*t2) + (3*t)) * 0.1)
                    + ((((-3)*t3) + (3*t2)) * 0.3)
                    + ((t3) * 0.2));
                    */
                Ponto p = Ponto(x,y,z);
                if (!is_clippable(p))
                {	 	  	 	    	 	    		    	    	  	 	
                    desenho.push_back(p);
                    clipping = false;
                }
                else if (!clipping)
                {
                    if (x < -XBORDER)
                    {
                        x = -XBORDER;
                    }

                    if (x > XBORDER)
                    {
                        x = XBORDER;
                    }
                    if (y < -YBORDER)
                    {
                        y = -YBORDER;
                    }

                    if (y > YBORDER)
                    {
                        y = YBORDER;
                    }
                    desenho.push_back(Ponto(x,y,z));
                    clipping = true;
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

std::list<Ponto> Curva2D::draw_spline(double scale, Matriz cart_to_scn)
{
    double dt = 1./20.;
    double dt2 = dt * dt;
    double dt3 = dt*dt*dt;
    double m_deltinha[4][4] = {{0,    0,     0,   1.},
                        {dt3,   dt2,   dt, 0},
                        {6.*dt2, 2.*dt2, 0,   0},
                        {6.*dt3, 0,     0,   0}};
    
    //double bspline[4][4] = {{-1./6.,  1./2., -1./2., 1./6.},
    //                        { 1./2., -1./1., 1./2., 0},
    //                       {-1./2.,  0, 1./2., 0},
    //                        {1./6.,  2./3.,  1./6., 0}};
                            
    double bspline[4][4] = {{0, 0, 0, 1./6.},
                            { 1./6., 1./2., 1./2., -1./2.},
                           {2./3.,  0, -1., 1./2.},
                            {1./6.,  -1./2.,  1./2., -1./6.}};
                            
    //double bspline[4][4] = {{1. , 0., 0., 0.},
    //                        {11./18, 1./9., -1./18., 1./9.},
    //                        {1./3.,  1./6., 0., -1./6.},
    //                        {1./6.,  1./6.,  1./6., 1./6.}};
                           
    
    std::list<Ponto> desenho;
    std::list<Ponto> temp = this->pontos;
    auto pt = temp.begin();
    if (this->get_size() >= 4)
    {
        Ponto p1 = Ponto(0,0,0);
        Ponto p2 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
        pt++;
        Ponto p3 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
        pt++;
        Ponto p4 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
        pt++;
        //desenho.push_back(Ponto(0,0));
        desenho.push_back(cart_to_scn.exec_transform(p2));
        desenho.push_back(cart_to_scn.exec_transform(p3));
        desenho.push_back(cart_to_scn.exec_transform(p4));
        desenho.push_back(cart_to_scn.exec_transform(p2));
        for (int i = 3; i < temp.size(); i++)
        {	 	  	 	    	 	    		    	    	  	 	
            p1 = p2;
            p2 = p3;
            p3 = p4;
            p4 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            Ponto p4 = Ponto(pt->get_x(), pt->get_y(), pt->get_z());
            pt++;
            
            double coef_x[4] = {};
            get_coef2(bspline, p1.get_x(), p2.get_x(), p3.get_x(), p4.get_x(), coef_x);
            double coef_y[4] = {};
            get_coef2(bspline, p1.get_y(), p2.get_y(), p3.get_y(), p4.get_y(), coef_y);
            double coef_z[4] = {};
            get_coef(bspline, p1.get_z(), p2.get_z(), p3.get_z(), p4.get_z(), coef_z);
            
            //desenho.push_back(cart_to_scn.exec_transform(Ponto(coef_x[3], coef_y[3], coef_z[4])));
            
            double dd_x[4] = {};
            get_coef(m_deltinha, coef_x[0], coef_x[1], coef_x[2], coef_x[3], dd_x);
            double dd_y[4] = {};
            get_coef(m_deltinha, coef_y[0], coef_y[1], coef_y[2], coef_y[3], dd_y);
            double dd_z[4] = {};
            get_coef2(m_deltinha, coef_z[0], coef_z[1], coef_z[2], coef_z[3], dd_z);
            /*
            desenho.push_back(cart_to_scn.exec_transform(Ponto(dd_x[0], dd_y[0], dd_z[0])));
            desenho.push_back(cart_to_scn.exec_transform(Ponto(dd_x[1], dd_y[1], dd_z[1])));
            desenho.push_back(cart_to_scn.exec_transform(Ponto(dd_x[2], dd_y[2], dd_z[2])));
            desenho.push_back(cart_to_scn.exec_transform(Ponto(dd_x[3], dd_y[3], dd_z[3])));
            desenho.push_back(cart_to_scn.exec_transform(Ponto(1, 1, 1)));
            */
            
            std::list<Ponto> temp = draw_curve_fwd_diff (20, 
                     p1.get_x(), dd_x[0], dd_x[1], dd_x[2], dd_x[3],
                     p1.get_y(), dd_y[0], dd_y[1], dd_y[2], dd_y[3], 
                     dd_z[0],    dd_z[0], dd_z[1], dd_z[2], dd_z[3],
                     cart_to_scn);
            
            desenho.insert(desenho.end(), temp.begin(), temp.end());
            //desenho.push_back(Ponto(dd_x[1],dd_y[1]));
        }	 	  	 	    	 	    		    	    	  	 	
        desenho.push_back(cart_to_scn.exec_transform(p4));
        //desenho.push_back(Ponto(0,0));
        //desenho.push_back(Ponto(dd_x[1],dd_y[1]));
        //desenho.push_back(Ponto(0.7,0.3));
    }
    else
    {
        desenho.push_back(Ponto(0,0));
        desenho.push_back(Ponto(10,10));
        //nao tem pelo menos 4 pontos
    }
    return desenho;

    
}

std::list<Ponto> Curva2D::draw_curve_fwd_diff( int n, 
                      double x, double Dx, double D2x, double D3x, double D4x,
                      double y, double Dy, double D2y, double D3y, double D4y,
                      double z, double Dz, double D2z, double D3z, double D4z,
                      Matriz cart_to_scn)
{
    std::list<Ponto> desenho;  
    int i = 0;
    Ponto p = cart_to_scn.exec_transform(Ponto(x, y, z));
    if (!is_clippable(p))
    {
       desenho.push_back(p); 
    }
    
    for (i=1; i < n; i++)
    {
        x = x + Dx;  Dx = Dx + D2x;  D2x = D2x + D3x; D3x = D3x + D4x;
        y = y + Dy;  Dy = Dy + D2y;  D2y = D2y + D3y; D3x = D3y + D4y;
        z = z + Dz;  Dz = Dz + D2z;  D2z = D2z + D3z; D3x = D3x + D4x;
        p = cart_to_scn.exec_transform(Ponto(x, y, z));
        if (!is_clippable(p))
        {	 	  	 	    	 	    		    	    	  	 	
           desenho.push_back(p); 
        }
    }
    return desenho;
}

void Curva2D::get_coef(double matriz[4][4], double p1, double p2, double p3, double p4, double* result)
{
    for (int i = 0; i<4; i++)
    {
        //result[i] = matriz[i][0] * p1 + matriz[i][1] * p2 + matriz[i][2] * p3 + matriz[i][3] * p4;
        result[i] = matriz[0][i] * p1 + matriz[1][i] * p2 + matriz[2][i] * p3 + matriz[3][i] * p4;
    }
}

void Curva2D::get_coef2(double matriz[4][4], double p1, double p2, double p3, double p4, double* result)
{
    for (int i = 0; i<4; i++)
    {
        result[i] = matriz[i][0] * p1 + matriz[i][1] * p2 + matriz[i][2] * p3 + matriz[i][3] * p4;
    }
}

bool Curva2D::is_clippable(Ponto p)
{
    if (p.get_x() > -XBORDER && p.get_x() < XBORDER && p.get_y() > -YBORDER && p.get_y() < YBORDER)
    {
        return false;
    }
    return true;
}

int Curva2D::get_num_curvas()
{
    return (int)(this->pontos.size()/4);
}	 	  	 	    	 	    		    	    	  	 	

Objeto Curva2D::to_objeto()
{
    Objeto o = Objeto();
    o.set_id(this->id);
    o.set_nome(this->nome);
    o.set_pontos(this->pontos);
    o.set_pontos_scn(this->pontos_scn);
    o.set_brush_size(this->brush_size);
    o.set_center(this->center);
    o.set_tipo(this->tipo);
    o.set_filled(this->filled);
    return o;
}

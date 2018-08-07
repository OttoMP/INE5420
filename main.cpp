#include <stdio.h>
#include <iostream>
#include "ponto.h"
#include "poligono.h"

using namespace std;

int main( int argc, const char* argv[] )
{
    Poligono pol("Quadrado");
    pol.addPonto(Ponto(1,2));
    //pol.addPonto(Ponto(2,3));
    
    std::list<Ponto> draw = pol.draw();
    
    /*
    cout << drawd.front().getX() << drawd.front().getY() << " \n";
        drawd.pop_front();
        
    cout << drawd.front().getX() << drawd.front().getY() << " \n";
        drawd.pop_front();
    
    cout << draw.front().getX() << draw.front().getY() << "  \n";
        draw.pop_front();
    
    cout << draw.front().getX() << draw.front().getY() << "  \n";
        draw.pop_front();
    
    cout << draw.front().getX() << draw.front().getY() << "  \n";
        draw.pop_front();
    */
    
    for (std::list<Ponto>::iterator it = draw.begin(); it != draw.end(); it++)
    {
        cout << it->getX() << ", " << it->getY() << " \n";
    }
    
}
#ifndef DESCRITOR_OBJ_H
#define DESCRITOR_OBJ_H

#include "poligono.h"

#include <list>
#include <fstream>
#include <iostream>

class descritorObj {

    public:
        descritorObj();
        ~descritorObj();

        void write(std::list<Poligono> display_file);
        Poligono read(std::string file);
};

#endif // DESCRITOR_OBJ_H

#ifndef DESCRITOR_OBJ_H
#define DESCRITOR_OBJ_H

#include "poligono.h"

class DescritorObj {

    public:
        std::string write(Poligono poly);
        Poligono read(std::string file);
};

#endif // DESCRITOR_OBJ_H

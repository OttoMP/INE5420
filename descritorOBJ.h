#ifndef DESCRITOR_OBJ_H
#define DESCRITOR_OBJ_H

#include "poligono.h"
#include <gtkmm/textview.h>

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

class descritorObj {

    public:
        descritorObj(Gtk::TextView& text_log);
        ~descritorObj();

        void write(std::list<Poligono> display_file, string name);
        std::list<Poligono> read(std::string file);

        template<typename Out>
        void split(const std::string &s, char delim, Out result);
		std::vector<std::string> split(const std::string &s, char delim);

	protected:
		Gtk::TextView& text_log_ref;
};

#endif // DESCRITOR_OBJ_H
	 	  	 	    	 	    		    	    	  	 	

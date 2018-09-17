#include "descritorOBJ.h"
using namespace std;

descritorObj::descritorObj(Gtk::TextView& text_log)
	: text_log_ref(text_log) {
}

descritorObj::~descritorObj() {}

void descritorObj::write(std::list<Objeto> display_file, string name) {
    ofstream new_file;
    new_file.open (name+".obj");

    for(auto ptr = display_file.begin(); ptr != display_file.end(); ptr++) {
        auto i = *ptr;
        new_file << "#nome " + i.get_nome() + "\n";
        new_file << "#tipo " + to_string(i.get_tipo()) + "\n";
        new_file << "#id " + to_string(i.get_id()) + "\n";
        if(i.get_filled())
            new_file << "#fill 1\n";
        else
            new_file << "#fill 0\n";

        std::list<Ponto> p_list = i.get_pontos();

		new_file << "#number_of_vertex " + to_string(p_list.size()) + "\n";
        for(Ponto p : p_list) {
           new_file << "v "
                       + to_string(p.get_x()) + " "
                       + to_string(p.get_y()) + " "
                       + to_string(p.get_z()) + "\n";
        }

        if(p_list.size() == 1) {
            new_file << "p -1\n";
        } else if(p_list.size() == 2) {
            new_file << "l -2 -1\n";
        } else {
            new_file << "f";
            for(auto i = p_list.size(); i > 0; i--) {
               new_file << " -" + to_string(i);
            }
            new_file << "\n";
        }
    }
    new_file.close();
    text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                        +"Display File salvo com sucesso.\n");
    return;
}

std::list<Objeto> descritorObj::read(std::string file) {
    std::list<Objeto> display_file;
    string line, nome, tipo, id, filled, vertex, info;
    ifstream myfile(file+".obj");

    if (myfile.is_open())
    {
		getline(myfile,nome);
		while(!myfile.eof()) {
			vector<string> nome_tokens = split(nome, ' ');

            getline(myfile,tipo);
			vector<string> tipo_tokens = split(tipo, ' ');

			getline(myfile,id);
			vector<string> id_tokens = split(id, ' ');

			getline(myfile,filled);
			vector<string> filled_tokens = split(filled, ' ');

            Objeto obj;

            obj.set_nome(nome_tokens[1]);
            obj.set_tipo(stoi(tipo_tokens[1]));
			obj.set_id(stoi(id_tokens[1]));
            if(filled_tokens[1] == "1")
                obj.set_filled(true);

			getline(myfile,vertex);
			vector<string> vertex_tokens = split(vertex, ' ');

            std::list<Ponto> recover_dots;
            auto nvertex = stoi(vertex_tokens[1]);
            for(auto i = 0; i < nvertex; i++) {
                getline(myfile,line);
                vector<string> tokens = split(line, ' ');
                recover_dots.push_back(Ponto(
                                            stof(tokens[1]),
                                            stof(tokens[2]),
                                            stof(tokens[3])));
            }
            obj.set_pontos(recover_dots);

    	    display_file.push_back(obj);


        // Get extra useless line
			getline(myfile, info);

        // trigger eof earlier
		    getline(myfile,nome);
		}

		myfile.close();
    	text_log_ref.get_buffer()->set_text(
                text_log_ref.get_buffer()->get_text()
				+"Arquivo carregado com sucesso.\n");
    } else {
    	text_log_ref.get_buffer()->set_text(
                text_log_ref.get_buffer()->get_text()
				+"Não foi possível abrir o arquivo\n");
    }
    return display_file;
}

template<typename Out>
void descritorObj::split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> descritorObj::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


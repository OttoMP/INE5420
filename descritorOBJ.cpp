#include "descritorOBJ.h"
using namespace std;

descritorObj::descritorObj(Gtk::TextView& text_log)
	: text_log_ref(text_log) {
}

descritorObj::~descritorObj() {}

void descritorObj::write(std::list<Poligono> display_file, string name) {
    ofstream new_file;
    new_file.open (name+".obj");

    for(auto poly : display_file) {
        new_file << "#nome " + poly.get_nome() + "\n";
        new_file << "#id " + to_string(poly.get_id()) + "\n";

        std::list<Ponto> p_list = poly.get_pontos();

		new_file << "#number of vertex " + to_string(p_list.size());
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
            for(auto i = p_list.size(); i > 0; i++) {
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

std::list<Poligono> descritorObj::read(std::string file) {
    std::list<Poligono> display_file;
    string line, nome, id, vertex, info;
    ifstream myfile(file);

    if (myfile.is_open())
    {
		while(!myfile.eof()) {
			getline(myfile,nome);
			vector<string> nome_tokens = split(line, ' ');

			getline(myfile,id);
			vector<string> id_tokens = split(line, ' ');

			Poligono poly(nome_tokens[1]);
			poly.set_id(stoi(id_tokens[1]));

			getline(myfile,vertex);
			vector<string> vertex_tokens = split(line, ' ');

			int nvertex = stoi(vertex_tokens[3]);
			for(auto i = 0; i < nvertex; i++) {
				getline(myfile,line);
				vector<string> tokens = split(line, ' ');
				poly.add_ponto(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
			}

			getline(myfile, info);
			display_file.push_back(poly);
		}
		myfile.close();
    	text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
											+"Arquivo carregado com sucesso.\n");
    } else {
    	text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
											+"Não foi possível abri o arquivo\n");
        cout << "Unable to open file";
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

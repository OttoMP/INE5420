#import "objeto.h"

void Objeto::set_brush_size(double brush)
{
    this->brush_size = brush;
}

std::list<Ponto> Objeto:: get_pontos() {
    return this->pontos;
}

void Objeto:: set_pontos(std::list<Ponto> pontos) {
    this->pontos = pontos;
}

int Objeto::get_size()
{
    return this->pontos.size();
}

double Objeto::get_brush_size()
{
    return this->brush_size;
}

string Objeto::get_nome()
{
    return this->nome;
}

void Objeto::set_nome(string nome) {
    this->nome = nome;
}

int Objeto::get_id() const{
    return this->id;
}

void Objeto::set_id(int new_id) {
    this->id = new_id;
}

Ponto Objeto::get_center()
{
    return this->center;
}

void Objeto::exec_transform(Matriz transform)
{
    this->center = transform.exec_transform(center);
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt = transform.exec_transform(*pt);
    }
}

void Objeto::exec_update_scn(Matriz transform)
{
    auto pt2 = this->pontos_scn.begin();
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt2 = transform.exec_transform(*pt);
        pt2++;
    }

}

bool Objeto::operator==(const Objeto& a) {
    return this->get_id() == a.get_id();
}

#ifndef RETA_H
#define RETA_H

class Reta{

private:
	Ponto* p1;
	Ponto* p2;

public:
	Reta(Ponto* p1, Ponto* p2);
	~Reta();

	Ponto getP1();
	Ponto getP2();

}


#endif //RETA_H
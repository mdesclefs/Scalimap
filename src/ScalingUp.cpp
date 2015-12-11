/*
 * ScalingUp.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "ScalingUp.h"
#include <iostream>
#include <vector>

ScalingUp::ScalingUp() : ScalingAlgorithm() {
	// TODO Auto-generated constructor stub

}

ScalingUp::ScalingUp(Image& image) : ScalingAlgorithm(&image) {
	// TODO Auto-generated constructor stub

}

ScalingUp::ScalingUp(Image * const image) : ScalingAlgorithm(image) {
	// TODO Auto-generated constructor stub

}

ScalingUp::~ScalingUp() {
	// TODO Auto-generated destructor stub
}

void ScalingUp::chooseMethod(std::vector<std::vector<Pixel*>> *& matrix, float factor, int x, int y){
	int translate = ceil(1 / factor);
	x*=translate;
	y*=translate;

	if(factor == 2){
		this->epx(matrix, x, y);
	}else{
		this->advMAME3x(matrix, x, y);
	}
}

void ScalingUp::epx(std::vector<std::vector<Pixel*>>*& matrix, int x, int y){
	// Implementation of EPX Algorithm Scaling by factor of two
	//		A				K	L
	//C		P		B		M	N
	//		D

	// A = 0 ; C = 1 ; B = 2 ; D = 3
	// 1		3		4		6
	/*
	 * K=P; L=P; M=P; N=P;
	 * If C==A then K=A;
	 * If A==B then L=B;
	 * If B==D then N=D;
	 * If D==C then M=C;
	 * If (A, B, C, D) three or more are identical then K=L=M=N=P
	 */

	std::vector<Pixel*> neighboor;
	neighboor =  this->_image->getNeighboor(x, y);
	Pixel* a,* b,* c,* d;
	a = neighboor[1];
	b = neighboor[4];
	c = neighboor[3];
	d = neighboor[6];

	Pixel* p,* k,* l,* m,* n;
	p = this->_image->getPixel(x, y);

	k=p;
	l=p;
	m=p;
	n=p;

	// C==A
	if(*c == *a)
		k=a;
	// A==B
	if(*a == *b)
		l=b;
	// B==D
	if(*b == *d)
		n=d;
	// D==C
	if(*d == *c)
		m=c;

	if(threeOrMoreEqual(a, b, c, d)){
		k=p;
		l=k;
		m=k;
		n=k;
	}

	int newX = (x*2);
	int newY = (y*2);

	(*matrix)[newY][newX] = k;
	(*matrix)[newY][newX+1] = l;
	(*matrix)[newY+1][newX] = m;
	(*matrix)[newY+1][newX+1] = n;
}

bool ScalingUp::threeOrMoreEqual(Pixel*& A, Pixel*& B, Pixel*& C, Pixel*& D){
	if(*A == *B && *B == *C && *C == *D) // A = B = C = D
		return true;
	if(*A == *B && *B == *C && *C != *D) // A = B = C != D
		return true;
	if(*A == *B && *B == *D && *C != *D) // A = B = D != C
		return true;
	if(*A == *C && *C == *D && *C != *B) // A = C = D != B
		return true;
	if(*B == *C && *C == *D && *A != *D) // B = C = D != A
		return true;

	return false;
}

void ScalingUp::advMAME3x(std::vector<std::vector<Pixel*>>*& matrix, int _x, int _y){

	std::vector<Pixel*> neighboor;
	neighboor =  this->_image->getNeighboor(_x, _y);

	Pixel* a,* b,* c,* d,* e,* f,* g,* h,* i;
	e = this->_image->getPixel(_x, _y);
	a = neighboor[0];
	b = neighboor[1];
	c = neighboor[2];
	d = neighboor[3];
	f = neighboor[4];
	g = neighboor[5];
	h = neighboor[6];
	i = neighboor[7];

	//R=S=T=U=V=W=X=Y=Z=E;
	Pixel* r,* s,* t,* u,* v,* w,* x,* y,* z;
	r = e;
	s = e;
	t = e;
	u = e;
	v = e;
	w = e;
	x = e;
	y = e;
	z = e;

	//If D==B and D!=H and B!=F then R=D;
	if(d == b and d != h and b != f)
		r = d;
	//If (D==B and D!=H and B!=F and E!=C) or (B==F and B!=D and F!=H and E!=A) then S=B;
	if((d == b and d != h and b != f and e != c) or (b == f and b != d and f != h and e != a))
		s = b;
	//If B==F and B!=D and F!=H then T=F;
	if(b == f and b != d and f != h)
		t = f;
	//If (H==D and H!=F and D!=B and E!=A) or (D==B and D!=H and B!=F and E!=G) then U=D;
	if((h == d and h != f and d != b and e != a) or (d == b and d != h and b != f and e != g))
		u = d;
	//If (B==F and B!=D and F!=H and E!=I) or (F==H and F!=B and H!=D and E!=C) then W=F;
	if((b == f and b != d and f != h and e != i) or (f == h and f != b and h != d and e != c))
		w = f;
	//If H==D and H!=F and D!=B then X=D;
	if(h == d and h != f and d != b)
		x = d;
	//If (F==H and F!=B and H!=D and E!=G) or (H==D and H!=F and D!=B and E!=I) then Y=H;
	if((f == h and f != b and h != d and e != g) or (h == d and h != f and d != b and e != i))
		y = h;
	//If F==H and F!=B and H!=D then Z=F;
	if(f == h and f != b and h != d)
		z = f;

	int newX = (_x*3);
	int newY = (_y*3);

	(*matrix)[newY][newX] = r;
	(*matrix)[newY][newX+1] = s;
	(*matrix)[newY][newX+2] = t;

	(*matrix)[newY+1][newX] = u;
	(*matrix)[newY+1][newX+1] = v;
	(*matrix)[newY+1][newX+2] = w;

	(*matrix)[newY+2][newX] = x;
	(*matrix)[newY+2][newX+1] = y;
	(*matrix)[newY+2][newX+2] = z;
}

/*
 * clasa punct
 */

#ifndef __PUNCT__
#define __PUNCT__
// punct: un set de coordonate (x,y) în spațiu
class punct
{
private:
	float x;					// coordonata X
	float y;					// coordonata Y

public:
	punct(float x=0, float y=0);
	void citire(void);
	void afisare(void);
	void afisare(char *prefix);
	float getx(void);
	float gety(void);
	//void setx(float x);
	//void sety(float y);
};

// calculează distanța dintre două puncte date
float distanta(punct *p1, punct *p2);
#endif

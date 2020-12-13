/*
  DigitalFilter - Bibliothek für verschiedene Digitale Filter

  Stefan Schlee, 2020
*/

#ifndef DigitalFilter_h
#define DigitalFilter_h

#include "Arduino.h"

/*
	Notch filter:
	fg: Filterfrequenz in Hz
	fs: Abtastfreqzenz in Hz
	a: Filtergüte, 0<a<1 schmaler bei 1
*/
class Notch_Order2
{

public:
	Notch_Order2(uint16_t fg, uint16_t fs, float a); //Konstruktor
	float get_Value();								 //get Filtered Value
	float update(float newVal);						 //update Value and return new Filtered Value
private:
	float u[2]; //Uk-1, Uk-2
	float y[3]; //Yk, Yk-1, Yk-2
	float k;	//stationäre Verstärkung
	float b1;
	float a0;
	float a1;
};

/*
	Biquad Filter direct form 1
	b0*u + b1*u-1 b2*u-2
	----------
	y + a1*y-1 + a2*y-2
*/
class Biquad
{

public:
	Biquad(float b0, float b1, float b2, float a1, float a2); //Konstruktor
	float get_Value();										  //get Filtered Value
	float update(float newVal);								  //update Value and return new Filtered Value
private:
	float u[2]; //Uk-1, Uk-2
	float y[3]; //Yk, Yk-1, Yk-2
	float b0, b1, b2;
	float a1, a2;
};

/*
	Pt1 Filter mit Grenzfrequens fg
*/
class PT1
{
public:
	PT1(float fg, float fs);
	float get_Value();
	float update(float newVal);
private:
	float u; //Uk-1
	float y[2]; //Yk, Yk-1
	float b; //Verstärkung Input
	float a1;  
};

#endif
